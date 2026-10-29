// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.session"] = canonical::text(std::string(iterator.packet_header->session.get()), '\0', false);
    values["packet.packetheader.sequencenumber"] = canonical::number(iterator.packet_header->sequence_number.get());
    values["packet.packetheader.messagecount"] = canonical::number(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(iterator.message_header->message_length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message->event_code.get()), ' ', false);
            values[entry + ".payload.systemeventmessage.currentyear"] = canonical::number(message->current_year.get());
            values[entry + ".payload.systemeventmessage.currentmonth"] = canonical::number(message->current_month.get());
            values[entry + ".payload.systemeventmessage.currentday"] = canonical::number(message->current_day.get());
            values[entry + ".payload.systemeventmessage.version"] = canonical::number(message->version.get());
            values[entry + ".payload.systemeventmessage.subversion"] = canonical::number(message->sub_version.get());
        } else if (iterator.message_type == protocol::ComplexStrategyDirectoryMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexstrategydirectorymessage";
            [[maybe_unused]] const auto* message = protocol::ComplexStrategyDirectoryMessage::parse(iterator.message);
            values[entry + ".payload.complexstrategydirectorymessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.complexstrategydirectorymessage.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.complexstrategydirectorymessage.strategytype"] = canonical::text(canonical::character(message->strategy_type.get()), ' ', false);
            values[entry + ".payload.complexstrategydirectorymessage.source"] = canonical::number(message->source.get());
            values[entry + ".payload.complexstrategydirectorymessage.underlyingsymbol"] = canonical::text(std::string(message->underlying_symbol.get()), ' ', false);
            values[entry + ".payload.complexstrategydirectorymessage.numberoflegs"] = canonical::number(message->number_of_legs.get());
        } else if (iterator.message_type == protocol::StrategyOpenClosedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategyopenclosedmessage";
            [[maybe_unused]] const auto* message = protocol::StrategyOpenClosedMessage::parse(iterator.message);
            values[entry + ".payload.strategyopenclosedmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.strategyopenclosedmessage.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.strategyopenclosedmessage.openstate"] = canonical::text(canonical::character(message->open_state.get()), ' ', false);
        } else if (iterator.message_type == protocol::StrategyTradingActionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategytradingactionmessage";
            [[maybe_unused]] const auto* message = protocol::StrategyTradingActionMessage::parse(iterator.message);
            values[entry + ".payload.strategytradingactionmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.strategytradingactionmessage.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.strategytradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message->current_trading_state.get()), ' ', false);
        } else if (iterator.message_type == protocol::StrategyBestBidAndAskUpdate::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidandaskupdate";
            [[maybe_unused]] const auto* message = protocol::StrategyBestBidAndAskUpdate::parse(iterator.message);
            values[entry + ".payload.strategybestbidandaskupdate.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.strategybestbidandaskupdate.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.strategybestbidandaskupdate.quotecondition"] = canonical::text(canonical::character(message->quote_condition.get()), ' ', false);
            values[entry + ".payload.strategybestbidandaskupdate.bidprice"] = canonical::scaled(message->bid_price.integer(), -4);
            values[entry + ".payload.strategybestbidandaskupdate.bidsize"] = canonical::number(message->bid_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.bidcustsize"] = canonical::number(message->bid_cust_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.bidprocustsize"] = canonical::number(message->bid_pro_cust_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.bidnttsize"] = canonical::number(message->bid_ntt_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.bidmarketsize"] = canonical::number(message->bid_market_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.bidnttmarketsize"] = canonical::number(message->bid_ntt_market_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.askprice"] = canonical::scaled(message->ask_price.integer(), -4);
            values[entry + ".payload.strategybestbidandaskupdate.asksize"] = canonical::number(message->ask_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.askcustsize"] = canonical::number(message->ask_cust_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.askprocustsize"] = canonical::number(message->ask_pro_cust_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.asknttsize"] = canonical::number(message->ask_ntt_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.askmarketsize"] = canonical::number(message->ask_market_size.get());
            values[entry + ".payload.strategybestbidandaskupdate.asknttmarketsize"] = canonical::number(message->ask_ntt_market_size.get());
        } else if (iterator.message_type == protocol::StrategyBestBidUpdate::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidupdate";
            [[maybe_unused]] const auto* message = protocol::StrategyBestBidUpdate::parse(iterator.message);
            values[entry + ".payload.strategybestbidupdate.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.strategybestbidupdate.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.strategybestbidupdate.quotecondition"] = canonical::text(canonical::character(message->quote_condition.get()), ' ', false);
            values[entry + ".payload.strategybestbidupdate.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".payload.strategybestbidupdate.size"] = canonical::number(message->size.get());
            values[entry + ".payload.strategybestbidupdate.custsize"] = canonical::number(message->cust_size.get());
            values[entry + ".payload.strategybestbidupdate.procustsize"] = canonical::number(message->pro_cust_size.get());
            values[entry + ".payload.strategybestbidupdate.nttsize"] = canonical::number(message->ntt_size.get());
            values[entry + ".payload.strategybestbidupdate.marketsize"] = canonical::number(message->market_size.get());
            values[entry + ".payload.strategybestbidupdate.nttmarketsize"] = canonical::number(message->ntt_market_size.get());
        } else if (iterator.message_type == protocol::StrategyBestAskUpdate::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategybestaskupdate";
            [[maybe_unused]] const auto* message = protocol::StrategyBestAskUpdate::parse(iterator.message);
            values[entry + ".payload.strategybestaskupdate.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.strategybestaskupdate.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.strategybestaskupdate.quotecondition"] = canonical::text(canonical::character(message->quote_condition.get()), ' ', false);
            values[entry + ".payload.strategybestaskupdate.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".payload.strategybestaskupdate.size"] = canonical::number(message->size.get());
            values[entry + ".payload.strategybestaskupdate.custsize"] = canonical::number(message->cust_size.get());
            values[entry + ".payload.strategybestaskupdate.procustsize"] = canonical::number(message->pro_cust_size.get());
            values[entry + ".payload.strategybestaskupdate.nttsize"] = canonical::number(message->ntt_size.get());
            values[entry + ".payload.strategybestaskupdate.marketsize"] = canonical::number(message->market_size.get());
            values[entry + ".payload.strategybestaskupdate.nttmarketsize"] = canonical::number(message->ntt_market_size.get());
        } else if (iterator.message_type == protocol::ComplexStrategyTickerMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexstrategytickermessage";
            [[maybe_unused]] const auto* message = protocol::ComplexStrategyTickerMessage::parse(iterator.message);
            values[entry + ".payload.complexstrategytickermessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.complexstrategytickermessage.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.complexstrategytickermessage.lastprice"] = canonical::scaled(message->last_price.integer(), -8);
            values[entry + ".payload.complexstrategytickermessage.size"] = canonical::number(message->size.get());
            values[entry + ".payload.complexstrategytickermessage.volume"] = canonical::number(message->volume.get());
            values[entry + ".payload.complexstrategytickermessage.high"] = canonical::number(message->high.get());
            values[entry + ".payload.complexstrategytickermessage.low"] = canonical::number(message->low.get());
            values[entry + ".payload.complexstrategytickermessage.first"] = canonical::number(message->first.get());
            values[entry + ".payload.complexstrategytickermessage.tradecondition"] = canonical::text(canonical::character(message->trade_condition.get()), ' ', false);
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
    std::printf("== Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 (modern values)\n");
    int failures = 0;
    failures += check("ComplexStrategyDirectoryMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/ComplexStrategyDirectoryMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/ComplexStrategyDirectoryMessage.values");
    failures += check("ComplexStrategyTickerMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/ComplexStrategyTickerMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/ComplexStrategyTickerMessage.values");
    failures += check("Heartbeat", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/Heartbeat.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/Heartbeat.values");
    failures += check("StrategyBestAskUpdate", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyBestAskUpdate.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyBestAskUpdate.values");
    failures += check("StrategyBestBidAndAskUpdate", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyBestBidAndAskUpdate.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyBestBidAndAskUpdate.values");
    failures += check("StrategyBestBidUpdate", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyBestBidUpdate.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyBestBidUpdate.values");
    failures += check("StrategyOpenClosedMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyOpenClosedMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyOpenClosedMessage.values");
    failures += check("StrategyTradingActionMessage", "Nasdaq/IseOptions.TopComboQuoteFeed.Itch.v1.0/StrategyTradingActionMessage.pcap", "nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/StrategyTradingActionMessage.values");
    return failures == 0 ? 0 : 1;
}
