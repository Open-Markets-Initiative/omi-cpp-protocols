// Siac.Cts.Output.Cta.v2.11.b canonical values, through the Modern iterator: every value Modern reads from
// each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/modern/siac/cts/output/cta/v2.11.b/definitions.hpp"

namespace protocol = ::siac::cts::output::cta::v2_11_b;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.blockheader.version"] = canonical::number(iterator.block_header->version.get());
    values["packet.blockheader.blocksize"] = canonical::number(iterator.block_header->block_size.get());
    values["packet.blockheader.datafeedindicator"] = canonical::text(canonical::character(iterator.block_header->data_feed_indicator.get()));
    values["packet.blockheader.retransmissionindicator"] = canonical::text(canonical::character(iterator.block_header->retransmission_indicator.get()));
    values["packet.blockheader.blocksequencenumber"] = canonical::number(iterator.block_header->block_sequence_number.get());
    values["packet.blockheader.messagesinblock"] = canonical::number(iterator.block_header->messages_in_block.get());
    values["packet.blockheader.sipblocktimestamp.seconds"] = canonical::number(iterator.block_header->sip_block_timestamp.seconds.get());
    values["packet.blockheader.sipblocktimestamp.nanoseconds"] = canonical::number(iterator.block_header->sip_block_timestamp.nanoseconds.get());
    values["packet.blockheader.blockchecksum"] = canonical::number(iterator.block_header->block_checksum.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messagecategory"] = canonical::text(canonical::character(iterator.message_header->message_category.get()));

        if (iterator.message_category == 'A') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.administrativemessage";
            [[maybe_unused]] const auto* message = protocol::AdministrativeMessage::parse(iterator.message);
            values[entry + ".categorypayload.administrativemessage.administrativemessagetype"] = canonical::text(canonical::character(message->administrative_message_type.get()));
        } else if (iterator.message_category == 'C') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.controlmessage";
            [[maybe_unused]] const auto* message = protocol::ControlMessage::parse(iterator.message);
            values[entry + ".categorypayload.controlmessage.controlmessagetype"] = canonical::text(canonical::character(message->control_message_type.get()));
        } else if (iterator.message_category == 'I') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.indicesmessage";
            [[maybe_unused]] const auto* message = protocol::IndicesMessage::parse(iterator.message);
            values[entry + ".categorypayload.indicesmessage.indicesmessagetype"] = canonical::text(canonical::character(message->indices_message_type.get()));
        } else if (iterator.message_category == 'M') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.marketstatusmessage";
            [[maybe_unused]] const auto* message = protocol::MarketStatusMessage::parse(iterator.message);
            values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagetype"] = canonical::text(canonical::character(message->market_status_message_type.get()));
        } else if (iterator.message_category == 'P') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.priordaymessage";
            [[maybe_unused]] const auto* message = protocol::PriorDayMessage::parse(iterator.message);
            values[entry + ".categorypayload.priordaymessage.priordaymessagetype"] = canonical::text(canonical::character(message->prior_day_message_type.get()));
        } else if (iterator.message_category == 'S') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.summarymessage";
            [[maybe_unused]] const auto* message = protocol::SummaryMessage::parse(iterator.message);
            values[entry + ".categorypayload.summarymessage.summarymessagetype"] = canonical::text(canonical::character(message->summary_message_type.get()));
        } else if (iterator.message_category == 'T') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.trademessage";
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            values[entry + ".categorypayload.trademessage.trademessagetype"] = canonical::text(canonical::character(message->trade_message_type.get()));
        }
    }

    return values;
}

// Read each datagram of a sample with Modern and hold it to the model's values
int check(const char* name, const char* capture, const char* expected) {
    const char* packets = std::getenv("OMI_PACKETS_DIR");

    if (packets == nullptr) {
        std::printf("FAIL: OMI_PACKETS_DIR is not set\n");
        return 1;
    }

    const auto model = canonical::load(canonical::root() + "/" + expected);
    std::vector<std::pair<std::string, std::int64_t>> sources;
    sources.emplace_back(std::string{packets} + "/" + capture, 0);

    packet::PcapIterator captures(sources);
    std::size_t datagram = 0;
    int differences = 0;

    while (captures.advance()) {
        const packet::Frame frame(captures.data(), captures.length());

        if (!frame.valid() || !frame.is_udp()) { continue; }

        if (datagram >= model.size()) {
            std::printf("FAIL %s: more datagrams than the model read\n", name);
            return 1;
        }

        differences += canonical::compare(name, datagram, model[datagram], read(frame));
        ++datagram;
    }

    if (datagram != model.size()) {
        std::printf("FAIL %s: %zu datagrams, the model read %zu\n", name, datagram, model.size());
        return 1;
    }

    if (differences == 0) {
        std::printf("ok   %s: %zu datagrams\n", name, datagram);
    }

    return differences == 0 ? 0 : 1;
}

}

int main() {
    std::printf("== Siac.Cts.Output.Cta.v2.11.b (modern values)\n");
    int failures = 0;
    failures += check("ConsolidatedStartOfDaySummaryMessage", "Siac/Cts.Output.Cta.v2.11.b/ConsolidatedStartOfDaySummaryMessage.pcap", "siac/cts/output/cta/v2.11.b/ConsolidatedStartOfDaySummaryMessage.values");
    failures += check("EndOfDayMessage", "Siac/Cts.Output.Cta.v2.11.b/EndOfDayMessage.pcap", "siac/cts/output/cta/v2.11.b/EndOfDayMessage.values");
    failures += check("EndOfEndOfDaySummaryMessage", "Siac/Cts.Output.Cta.v2.11.b/EndOfEndOfDaySummaryMessage.pcap", "siac/cts/output/cta/v2.11.b/EndOfEndOfDaySummaryMessage.values");
    failures += check("EndOfStartOfDaySummaryMessage", "Siac/Cts.Output.Cta.v2.11.b/EndOfStartOfDaySummaryMessage.pcap", "siac/cts/output/cta/v2.11.b/EndOfStartOfDaySummaryMessage.values");
    failures += check("FractionalApproximateAdjustedVolumeMarketCenterMessage", "Siac/Cts.Output.Cta.v2.11.b/FractionalApproximateAdjustedVolumeMarketCenterMessage.pcap", "siac/cts/output/cta/v2.11.b/FractionalApproximateAdjustedVolumeMarketCenterMessage.values");
    failures += check("FractionalConsolidatedEndOfDaySummaryMessage", "Siac/Cts.Output.Cta.v2.11.b/FractionalConsolidatedEndOfDaySummaryMessage.pcap", "siac/cts/output/cta/v2.11.b/FractionalConsolidatedEndOfDaySummaryMessage.values");
    failures += check("FractionalLongTradeMessage", "Siac/Cts.Output.Cta.v2.11.b/FractionalLongTradeMessage.pcap", "siac/cts/output/cta/v2.11.b/FractionalLongTradeMessage.values");
    failures += check("FractionalParticipantEndOfDaySummaryMessage", "Siac/Cts.Output.Cta.v2.11.b/FractionalParticipantEndOfDaySummaryMessage.pcap", "siac/cts/output/cta/v2.11.b/FractionalParticipantEndOfDaySummaryMessage.values");
    failures += check("FractionalPriorDayTradeCancelErrorMessage", "Siac/Cts.Output.Cta.v2.11.b/FractionalPriorDayTradeCancelErrorMessage.pcap", "siac/cts/output/cta/v2.11.b/FractionalPriorDayTradeCancelErrorMessage.values");
    failures += check("FractionalPriorDayTradeMessage", "Siac/Cts.Output.Cta.v2.11.b/FractionalPriorDayTradeMessage.pcap", "siac/cts/output/cta/v2.11.b/FractionalPriorDayTradeMessage.values");
    failures += check("FractionalTradeCancelErrorMessage", "Siac/Cts.Output.Cta.v2.11.b/FractionalTradeCancelErrorMessage.pcap", "siac/cts/output/cta/v2.11.b/FractionalTradeCancelErrorMessage.values");
    failures += check("LineIntegrityMessage", "Siac/Cts.Output.Cta.v2.11.b/LineIntegrityMessage.pcap", "siac/cts/output/cta/v2.11.b/LineIntegrityMessage.values");
    failures += check("MarketWideCircuitBreakerDeclineLevelStatusMessage", "Siac/Cts.Output.Cta.v2.11.b/MarketWideCircuitBreakerDeclineLevelStatusMessage.pcap", "siac/cts/output/cta/v2.11.b/MarketWideCircuitBreakerDeclineLevelStatusMessage.values");
    failures += check("ParticipantStartOfDaySummaryMessage", "Siac/Cts.Output.Cta.v2.11.b/ParticipantStartOfDaySummaryMessage.pcap", "siac/cts/output/cta/v2.11.b/ParticipantStartOfDaySummaryMessage.values");
    failures += check("StartOfDayMessage", "Siac/Cts.Output.Cta.v2.11.b/StartOfDayMessage.pcap", "siac/cts/output/cta/v2.11.b/StartOfDayMessage.values");
    failures += check("StartOfEndOfDaySummaryMessage", "Siac/Cts.Output.Cta.v2.11.b/StartOfEndOfDaySummaryMessage.pcap", "siac/cts/output/cta/v2.11.b/StartOfEndOfDaySummaryMessage.values");
    failures += check("StartOfStartOfDaySummaryMessage", "Siac/Cts.Output.Cta.v2.11.b/StartOfStartOfDaySummaryMessage.pcap", "siac/cts/output/cta/v2.11.b/StartOfStartOfDaySummaryMessage.values");
    failures += check("SymbolReferenceDataMessage", "Siac/Cts.Output.Cta.v2.11.b/SymbolReferenceDataMessage.pcap", "siac/cts/output/cta/v2.11.b/SymbolReferenceDataMessage.values");
    failures += check("TradingStatusMessage", "Siac/Cts.Output.Cta.v2.11.b/TradingStatusMessage.pcap", "siac/cts/output/cta/v2.11.b/TradingStatusMessage.values");
    return failures == 0 ? 0 : 1;
}