// Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 canonical values, through the Classes Packet: every value Classes decodes from
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
#include "cpp/binary/classes/nasdaq/iseoptions/ordercombofeed/itch/v1.1/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

namespace {

// The values the Classes Packet decodes from one datagram, by indexed address. A datagram it cannot
// decode is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        values["(does not decode)"] = error.what();
        return values;
    }

    values["packet.packetheader.session"] = canonical::text(std::string(packet.packet_header().session()), '\0', false);
    values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
    values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(each.message_header().message_length());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(each.message_header().message_type()));

        if (const auto* message = dynamic_cast<const protocol::SystemEventMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
            values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character((*message).event_code()), ' ', false);
            values[entry + ".payload.systemeventmessage.currentyear"] = canonical::number((*message).current_year());
            values[entry + ".payload.systemeventmessage.currentmonth"] = canonical::number((*message).current_month());
            values[entry + ".payload.systemeventmessage.currentday"] = canonical::number((*message).current_day());
            values[entry + ".payload.systemeventmessage.version"] = canonical::number((*message).version());
            values[entry + ".payload.systemeventmessage.subversion"] = canonical::number((*message).sub_version());
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyDirectoryMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexstrategydirectorymessage";
            values[entry + ".payload.complexstrategydirectorymessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.complexstrategydirectorymessage.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.complexstrategydirectorymessage.strategytype"] = canonical::text(canonical::character((*message).strategy_type()), ' ', false);
            values[entry + ".payload.complexstrategydirectorymessage.source"] = canonical::number((*message).source());
            values[entry + ".payload.complexstrategydirectorymessage.underlyingsymbol"] = canonical::text(std::string((*message).underlying_symbol()), ' ', false);
            values[entry + ".payload.complexstrategydirectorymessage.numberoflegs"] = canonical::number((*message).number_of_legs());
        } else if (const auto* message = dynamic_cast<const protocol::StrategyTradingActionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategytradingactionmessage";
            values[entry + ".payload.strategytradingactionmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.strategytradingactionmessage.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.strategytradingactionmessage.currenttradingstate"] = canonical::text(canonical::character((*message).current_trading_state()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::StrategyOpenClosedMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.strategyopenclosedmessage";
            values[entry + ".payload.strategyopenclosedmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.strategyopenclosedmessage.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.strategyopenclosedmessage.openstate"] = canonical::text(canonical::character((*message).open_state()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyOrderOnBookMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexstrategyorderonbookmessage";
            values[entry + ".payload.complexstrategyorderonbookmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.complexstrategyorderonbookmessage.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.complexstrategyorderonbookmessage.ordertype"] = canonical::text(canonical::character((*message).order_type()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.complexstrategyorderonbookmessage.size"] = canonical::number((*message).size());
            values[entry + ".payload.complexstrategyorderonbookmessage.execflag"] = canonical::text(canonical::character((*message).exec_flag()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.ordercapacity"] = canonical::text(canonical::character((*message).order_capacity()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.scope"] = canonical::text(canonical::character((*message).scope()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.ownerid"] = canonical::text(std::string((*message).owner_id()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.giveup"] = canonical::text(std::string((*message).giveup()), ' ', false);
            values[entry + ".payload.complexstrategyorderonbookmessage.cmta"] = canonical::text(std::string((*message).cmta()), ' ', false);
        } else if (const auto* message = dynamic_cast<const protocol::ComplexStrategyAuctionMessage*>(each.message())) {
            values[entry + ".payload"] = "packet.messages.message.payload.complexstrategyauctionmessage";
            values[entry + ".payload.complexstrategyauctionmessage.timestamp"] = canonical::number((*message).timestamp());
            values[entry + ".payload.complexstrategyauctionmessage.strategyid"] = canonical::number((*message).strategy_id());
            values[entry + ".payload.complexstrategyauctionmessage.auctionid"] = canonical::number((*message).auction_id());
            values[entry + ".payload.complexstrategyauctionmessage.ordertype"] = canonical::text(canonical::character((*message).order_type()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.side"] = canonical::text(canonical::character((*message).side()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.price"] = canonical::scaled((*message).price().mantissa(), (*message).price().exponent());
            values[entry + ".payload.complexstrategyauctionmessage.size"] = canonical::number((*message).size());
            values[entry + ".payload.complexstrategyauctionmessage.execflag"] = canonical::text(canonical::character((*message).exec_flag()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.ordercapacity"] = canonical::text(canonical::character((*message).order_capacity()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.scope"] = canonical::text(canonical::character((*message).scope()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.ownerid"] = canonical::text(std::string((*message).owner_id()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.giveup"] = canonical::text(std::string((*message).giveup()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.cmta"] = canonical::text(std::string((*message).cmta()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.auctionevent"] = canonical::text(canonical::character((*message).auction_event()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.auctiontype"] = canonical::text(canonical::character((*message).auction_type()), ' ', false);
            values[entry + ".payload.complexstrategyauctionmessage.numberofresponses"] = canonical::number((*message).number_of_responses());
        }
    }

    return values;
}

// Read each datagram of a sample with Classes and hold it to the model's values
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
    std::printf("== Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 (classes values)\n");
    int failures = 0;
    failures += check("ComplexStrategyAuctionMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/ComplexStrategyAuctionMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/ComplexStrategyAuctionMessage.values");
    failures += check("ComplexStrategyDirectoryMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/ComplexStrategyDirectoryMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/ComplexStrategyDirectoryMessage.values");
    failures += check("ComplexStrategyOrderOnBookMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/ComplexStrategyOrderOnBookMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/ComplexStrategyOrderOnBookMessage.values");
    failures += check("Heartbeat", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/Heartbeat.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/Heartbeat.values");
    failures += check("StrategyOpenClosedMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/StrategyOpenClosedMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/StrategyOpenClosedMessage.values");
    failures += check("StrategyTradingActionMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/StrategyTradingActionMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/StrategyTradingActionMessage.values");
    return failures == 0 ? 0 : 1;
}
