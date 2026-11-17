// Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 canonical values, through the Advanced session layer: every value Advanced
// reads from each sample, at its address, held to what the model reads.

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
#include "cpp/binary/advanced/nasdaq/iseoptions/ordercombofeed/itch/v1.1/messages/session.hpp"

namespace protocol = ::nasdaq::iseoptions::ordercombofeed::itch::v1_1;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        values["packet.packetheader.session"] = canonical::text(std::string(header.session.get().value()), '\0', false);
        values["packet.packetheader.sequencenumber"] = canonical::number(header.sequence_number.get().value());
        values["packet.packetheader.messagecount"] = canonical::number(header.message_count.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.fields.event_code.get().value()), ' ', false);
        values[entry + ".payload.systemeventmessage.currentyear"] = canonical::number(message.fields.current_year.get().value());
        values[entry + ".payload.systemeventmessage.currentmonth"] = canonical::number(message.fields.current_month.get().value());
        values[entry + ".payload.systemeventmessage.currentday"] = canonical::number(message.fields.current_day.get().value());
        values[entry + ".payload.systemeventmessage.version"] = canonical::number(message.fields.version.get().value());
        values[entry + ".payload.systemeventmessage.subversion"] = canonical::number(message.fields.sub_version.get().value());
    }

    void on_message(const protocol::complex_strategy_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.complexstrategydirectorymessage";
        values[entry + ".payload.complexstrategydirectorymessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.complexstrategydirectorymessage.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.complexstrategydirectorymessage.strategytype"] = canonical::text(canonical::character(message.fields.strategy_type.get().value()), ' ', false);
        values[entry + ".payload.complexstrategydirectorymessage.source"] = canonical::number(message.fields.source.get().value());
        values[entry + ".payload.complexstrategydirectorymessage.underlyingsymbol"] = canonical::text(std::string(message.fields.underlying_symbol.get().value()), ' ', false);
        values[entry + ".payload.complexstrategydirectorymessage.numberoflegs"] = canonical::number(message.fields.number_of_legs.get().value());
    }

    void on_message(const protocol::strategy_trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.strategytradingactionmessage";
        values[entry + ".payload.strategytradingactionmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.strategytradingactionmessage.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.strategytradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message.fields.current_trading_state.get().value()), ' ', false);
    }

    void on_message(const protocol::strategy_open_closed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.strategyopenclosedmessage";
        values[entry + ".payload.strategyopenclosedmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.strategyopenclosedmessage.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.strategyopenclosedmessage.openstate"] = canonical::text(canonical::character(message.fields.open_state.get().value()), ' ', false);
    }

    void on_message(const protocol::complex_strategy_order_on_book_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.complexstrategyorderonbookmessage";
        values[entry + ".payload.complexstrategyorderonbookmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.complexstrategyorderonbookmessage.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.complexstrategyorderonbookmessage.ordertype"] = canonical::text(canonical::character(message.fields.order_type.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyorderonbookmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyorderonbookmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.complexstrategyorderonbookmessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".payload.complexstrategyorderonbookmessage.execflag"] = canonical::text(canonical::character(message.fields.exec_flag.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyorderonbookmessage.ordercapacity"] = canonical::text(canonical::character(message.fields.order_capacity.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyorderonbookmessage.scope"] = canonical::text(canonical::character(message.fields.scope.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyorderonbookmessage.ownerid"] = canonical::text(std::string(message.fields.owner_id.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyorderonbookmessage.giveup"] = canonical::text(std::string(message.fields.giveup.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyorderonbookmessage.cmta"] = canonical::text(std::string(message.fields.cmta.get().value()), ' ', false);
    }

    void on_message(const protocol::complex_strategy_auction_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.complexstrategyauctionmessage";
        values[entry + ".payload.complexstrategyauctionmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.complexstrategyauctionmessage.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.complexstrategyauctionmessage.auctionid"] = canonical::number(message.fields.auction_id.get().value());
        values[entry + ".payload.complexstrategyauctionmessage.ordertype"] = canonical::text(canonical::character(message.fields.order_type.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.side"] = canonical::text(canonical::character(message.fields.side.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.complexstrategyauctionmessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".payload.complexstrategyauctionmessage.execflag"] = canonical::text(canonical::character(message.fields.exec_flag.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.ordercapacity"] = canonical::text(canonical::character(message.fields.order_capacity.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.scope"] = canonical::text(canonical::character(message.fields.scope.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.ownerid"] = canonical::text(std::string(message.fields.owner_id.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.giveup"] = canonical::text(std::string(message.fields.giveup.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.cmta"] = canonical::text(std::string(message.fields.cmta.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.auctionevent"] = canonical::text(canonical::character(message.fields.auction_event.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.auctiontype"] = canonical::text(canonical::character(message.fields.auction_type.get().value()), ' ', false);
        values[entry + ".payload.complexstrategyauctionmessage.numberofresponses"] = canonical::number(message.fields.number_of_responses.get().value());
    }
};

// The values Advanced reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.values;
}

// Read each datagram of a sample with Advanced and hold it to the model's values
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
    std::printf("== Nasdaq.IseOptions.OrderComboFeed.Itch.v1.1 (advanced values)\n");
    int failures = 0;
    failures += check("ComplexStrategyAuctionMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/ComplexStrategyAuctionMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/ComplexStrategyAuctionMessage.values");
    failures += check("ComplexStrategyDirectoryMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/ComplexStrategyDirectoryMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/ComplexStrategyDirectoryMessage.values");
    failures += check("ComplexStrategyOrderOnBookMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/ComplexStrategyOrderOnBookMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/ComplexStrategyOrderOnBookMessage.values");
    failures += check("Heartbeat", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/Heartbeat.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/Heartbeat.values");
    failures += check("StrategyOpenClosedMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/StrategyOpenClosedMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/StrategyOpenClosedMessage.values");
    failures += check("StrategyTradingActionMessage", "Nasdaq/IseOptions.OrderComboFeed.Itch.v1.1/StrategyTradingActionMessage.pcap", "nasdaq/iseoptions/ordercombofeed/itch/v1.1/StrategyTradingActionMessage.values");
    return failures == 0 ? 0 : 1;
}
