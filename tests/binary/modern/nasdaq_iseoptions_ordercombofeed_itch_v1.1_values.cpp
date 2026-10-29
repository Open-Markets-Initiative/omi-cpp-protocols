// Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/nasdaq/iseoptions/ordercombofeed/itch/v1.1/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

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
        } else if (iterator.message_type == protocol::StrategyTradingActionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategytradingactionmessage";
            [[maybe_unused]] const auto* message = protocol::StrategyTradingActionMessage::parse(iterator.message);
            values[entry + ".payload.strategytradingactionmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.strategytradingactionmessage.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.strategytradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message->current_trading_state.get()), ' ', false);
        } else if (iterator.message_type == protocol::StrategyOpenClosedMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategyopenclosedmessage";
            [[maybe_unused]] const auto* message = protocol::StrategyOpenClosedMessage::parse(iterator.message);
            values[entry + ".payload.strategyopenclosedmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.strategyopenclosedmessage.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.strategyopenclosedmessage.openstate"] = canonical::text(canonical::character(message->open_state.get()), ' ', false);
        } else if (iterator.message_type == protocol::ComplexStrategyOrderOnBookMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexstrategyorderonbookmessage";
            [[maybe_unused]] const auto* message = protocol::ComplexStrategyOrderOnBookMessage::parse(iterator.message);
            values[entry + ".payload.complexstrategyorderonbookmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.complexstrategyorderonbookmessage.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.complexstrategyorderonbookmessage.ordertype"] = canonical::text(canonical::character(message->order_type.get()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".payload.complexstrategyorderonbookmessage.size"] = canonical::number(message->size.get());
            values[entry + ".payload.complexstrategyorderonbookmessage.execflag"] = canonical::text(canonical::character(message->exec_flag.get()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.ordercapacity"] = canonical::text(canonical::character(message->order_capacity.get()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.scope"] = canonical::text(canonical::character(message->scope.get()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.ownerid"] = canonical::text(std::string(message->owner_id.get()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.giveup"] = canonical::text(std::string(message->giveup.get()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.cmta"] = canonical::text(std::string(message->cmta.get()), ' ', false);
        } else if (iterator.message_type == protocol::ComplexStrategyAuctionMessage::message_type) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexstrategyauctionmessage";
            [[maybe_unused]] const auto* message = protocol::ComplexStrategyAuctionMessage::parse(iterator.message);
            values[entry + ".payload.complexstrategyauctionmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.complexstrategyauctionmessage.strategyid"] = canonical::number(message->strategy_id.get());
            values[entry + ".payload.complexstrategyauctionmessage.auctionid"] = canonical::number(message->auction_id.get());
            values[entry + ".payload.complexstrategyauctionmessage.ordertype"] = canonical::text(canonical::character(message->order_type.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.price"] = canonical::scaled(message->price.integer(), -4);
            values[entry + ".payload.complexstrategyauctionmessage.size"] = canonical::number(message->size.get());
            values[entry + ".payload.complexstrategyauctionmessage.execflag"] = canonical::text(canonical::character(message->exec_flag.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.ordercapacity"] = canonical::text(canonical::character(message->order_capacity.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.scope"] = canonical::text(canonical::character(message->scope.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.ownerid"] = canonical::text(std::string(message->owner_id.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.giveup"] = canonical::text(std::string(message->giveup.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.cmta"] = canonical::text(std::string(message->cmta.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.auctionevent"] = canonical::text(canonical::character(message->auction_event.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.auctiontype"] = canonical::text(canonical::character(message->auction_type.get()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.numberofresponses"] = canonical::number(message->number_of_responses.get());
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
    std::printf("== Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 (modern values)\n");
    int failures = 0;
    failures += check("ComplexStrategyAuctionMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/ComplexStrategyAuctionMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/ComplexStrategyAuctionMessage.values");
    failures += check("ComplexStrategyDirectoryMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/ComplexStrategyDirectoryMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/ComplexStrategyDirectoryMessage.values");
    failures += check("ComplexStrategyOrderOnBookMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/ComplexStrategyOrderOnBookMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/ComplexStrategyOrderOnBookMessage.values");
    failures += check("Heartbeat", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/Heartbeat.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/Heartbeat.values");
    failures += check("StrategyOpenClosedMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/StrategyOpenClosedMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/StrategyOpenClosedMessage.values");
    failures += check("StrategyTradingActionMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/StrategyTradingActionMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/StrategyTradingActionMessage.values");
    return failures == 0 ? 0 : 1;
}
