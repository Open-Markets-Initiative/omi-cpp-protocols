// Siac.Cqs.Output.Cta.v2.10.a canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/modern/siac/cqs/output/cta/v2.10.a/definitions.hpp"

namespace protocol = ::siac::cqs::output::cta::v2_10_a;

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
        } else if (iterator.message_category == 'M') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.marketstatusmessage";
            [[maybe_unused]] const auto* message = protocol::MarketStatusMessage::parse(iterator.message);
            values[entry + ".categorypayload.marketstatusmessage.marketstatusmessagetype"] = canonical::text(canonical::character(message->market_status_message_type.get()));
        } else if (iterator.message_category == 'Q') {
            values[entry + ".categorypayload"] = "packet.message.categorypayload.quotemessage";
            [[maybe_unused]] const auto* message = protocol::QuoteMessage::parse(iterator.message);
            values[entry + ".categorypayload.quotemessage.quotemessagetype"] = canonical::text(canonical::character(message->quote_message_type.get()));
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
    std::printf("== Siac.Cqs.Output.Cta.v2.10.a (modern values)\n");
    int failures = 0;
    failures += check("EndOfDayMessage", "Siac/Cqs.Output.Cta.v2.10.a/EndOfDayMessage.pcap", "siac/cqs/output/cta/v2.10.a/EndOfDayMessage.values");
    failures += check("FinraCloseMessage", "Siac/Cqs.Output.Cta.v2.10.a/FinraCloseMessage.pcap", "siac/cqs/output/cta/v2.10.a/FinraCloseMessage.values");
    failures += check("FinraOpenMessage", "Siac/Cqs.Output.Cta.v2.10.a/FinraOpenMessage.pcap", "siac/cqs/output/cta/v2.10.a/FinraOpenMessage.values");
    failures += check("LineIntegrityMessage", "Siac/Cqs.Output.Cta.v2.10.a/LineIntegrityMessage.pcap", "siac/cqs/output/cta/v2.10.a/LineIntegrityMessage.values");
    failures += check("LongQuoteMessage", "Siac/Cqs.Output.Cta.v2.10.a/LongQuoteMessage.pcap", "siac/cqs/output/cta/v2.10.a/LongQuoteMessage.values");
    failures += check("MarketWideCircuitBreakerDeclineLevelStatusMessage", "Siac/Cqs.Output.Cta.v2.10.a/MarketWideCircuitBreakerDeclineLevelStatusMessage.pcap", "siac/cqs/output/cta/v2.10.a/MarketWideCircuitBreakerDeclineLevelStatusMessage.values");
    failures += check("StartOfDayMessage", "Siac/Cqs.Output.Cta.v2.10.a/StartOfDayMessage.pcap", "siac/cqs/output/cta/v2.10.a/StartOfDayMessage.values");
    failures += check("SymbolReferenceDataMessage", "Siac/Cqs.Output.Cta.v2.10.a/SymbolReferenceDataMessage.pcap", "siac/cqs/output/cta/v2.10.a/SymbolReferenceDataMessage.values");
    return failures == 0 ? 0 : 1;
}