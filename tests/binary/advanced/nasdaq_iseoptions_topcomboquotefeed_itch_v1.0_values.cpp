// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 canonical values, through the Advanced session layer: every value Advanced
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
#include "cpp/binary/advanced/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/messages/session.hpp"

namespace protocol = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

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

    void on_message(const protocol::strategy_open_closed_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.strategyopenclosedmessage";
        values[entry + ".payload.strategyopenclosedmessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.strategyopenclosedmessage.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.strategyopenclosedmessage.openstate"] = canonical::text(canonical::character(message.fields.open_state.get().value()), ' ', false);
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

    void on_message(const protocol::strategy_best_bid_and_ask_update& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidandaskupdate";
        values[entry + ".payload.strategybestbidandaskupdate.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.quotecondition"] = canonical::text(canonical::character(message.fields.quote_condition.get().value()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
        values[entry + ".payload.strategybestbidandaskupdate.bidprice"] = canonical::scaled(message.fields.bid_price.get().value(), -4);
        values[entry + ".payload.strategybestbidandaskupdate.bidsize"] = canonical::number(message.fields.bid_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.bidcustsize"] = canonical::number(message.fields.bid_cust_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.bidprocustsize"] = canonical::number(message.fields.bid_pro_cust_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.bidnttsize"] = canonical::number(message.fields.bid_ntt_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.bidmarketsize"] = canonical::number(message.fields.bid_market_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.bidnttmarketsize"] = canonical::number(message.fields.bid_ntt_market_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.askprice"] = canonical::scaled(message.fields.ask_price.get().value(), -4);
        values[entry + ".payload.strategybestbidandaskupdate.asksize"] = canonical::number(message.fields.ask_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.askcustsize"] = canonical::number(message.fields.ask_cust_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.askprocustsize"] = canonical::number(message.fields.ask_pro_cust_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.asknttsize"] = canonical::number(message.fields.ask_ntt_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.askmarketsize"] = canonical::number(message.fields.ask_market_size.get().value());
        values[entry + ".payload.strategybestbidandaskupdate.asknttmarketsize"] = canonical::number(message.fields.ask_ntt_market_size.get().value());
    }

    void on_message(const protocol::strategy_best_bid_update& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidupdate";
        values[entry + ".payload.strategybestbidupdate.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.strategybestbidupdate.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.strategybestbidupdate.quotecondition"] = canonical::text(canonical::character(message.fields.quote_condition.get().value()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
        values[entry + ".payload.strategybestbidupdate.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.strategybestbidupdate.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".payload.strategybestbidupdate.custsize"] = canonical::number(message.fields.cust_size.get().value());
        values[entry + ".payload.strategybestbidupdate.procustsize"] = canonical::number(message.fields.pro_cust_size.get().value());
        values[entry + ".payload.strategybestbidupdate.nttsize"] = canonical::number(message.fields.ntt_size.get().value());
        values[entry + ".payload.strategybestbidupdate.marketsize"] = canonical::number(message.fields.market_size.get().value());
        values[entry + ".payload.strategybestbidupdate.nttmarketsize"] = canonical::number(message.fields.ntt_market_size.get().value());
    }

    void on_message(const protocol::strategy_best_ask_update& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.strategybestaskupdate";
        values[entry + ".payload.strategybestaskupdate.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.strategybestaskupdate.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.strategybestaskupdate.quotecondition"] = canonical::text(canonical::character(message.fields.quote_condition.get().value()), ' ', false, {std::string_view(" ", 1), std::string_view("", 0)});
        values[entry + ".payload.strategybestaskupdate.price"] = canonical::scaled(message.fields.price.get().value(), -4);
        values[entry + ".payload.strategybestaskupdate.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".payload.strategybestaskupdate.custsize"] = canonical::number(message.fields.cust_size.get().value());
        values[entry + ".payload.strategybestaskupdate.procustsize"] = canonical::number(message.fields.pro_cust_size.get().value());
        values[entry + ".payload.strategybestaskupdate.nttsize"] = canonical::number(message.fields.ntt_size.get().value());
        values[entry + ".payload.strategybestaskupdate.marketsize"] = canonical::number(message.fields.market_size.get().value());
        values[entry + ".payload.strategybestaskupdate.nttmarketsize"] = canonical::number(message.fields.ntt_market_size.get().value());
    }

    void on_message(const protocol::complex_strategy_ticker_message& message, std::uint64_t, const protocol::packet_header&) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.messagelength"] = canonical::number(message.header.message_length.get().value());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(message.header.message_type.get().value()));
        values[entry + ".payload"] = "packet.messages.message.payload.complexstrategytickermessage";
        values[entry + ".payload.complexstrategytickermessage.timestamp"] = canonical::number(message.fields.timestamp.get().value());
        values[entry + ".payload.complexstrategytickermessage.strategyid"] = canonical::number(message.fields.strategy_id.get().value());
        values[entry + ".payload.complexstrategytickermessage.lastprice"] = canonical::scaled(message.fields.last_price.get().value(), -8);
        values[entry + ".payload.complexstrategytickermessage.size"] = canonical::number(message.fields.size.get().value());
        values[entry + ".payload.complexstrategytickermessage.volume"] = canonical::number(message.fields.volume.get().value());
        values[entry + ".payload.complexstrategytickermessage.high"] = canonical::scaled(message.fields.high.get().value(), -8);
        values[entry + ".payload.complexstrategytickermessage.low"] = canonical::scaled(message.fields.low.get().value(), -8);
        values[entry + ".payload.complexstrategytickermessage.first"] = canonical::scaled(message.fields.first.get().value(), -8);
        values[entry + ".payload.complexstrategytickermessage.tradecondition"] = canonical::text(canonical::character(message.fields.trade_condition.get().value()), ' ', false);
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
    std::printf("== Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 (advanced values)\n");
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
