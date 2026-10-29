// Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 canonical values, through the Flyweight reader: every value Flyweight reads
// from each sample, at its address, held to what the model reads.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <span>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "tests/canonical/Canonical.hpp"
#include "cpp/binary/flyweight/nasdaq/iseoptions/topcomboquotefeed/itch/v1.0/definitions.hpp"

namespace protocol = ::nasdaq::iseoptions::topcomboquotefeed::itch::v1_0;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.session"] = canonical::text(std::string(packet.packet_header().session()), '\0', false);
        values["packet.packetheader.sequencenumber"] = canonical::number(packet.packet_header().sequence_number());
        values["packet.packetheader.messagecount"] = canonical::number(packet.packet_header().message_count());
    }

    // a message this test prints no values of, or a code no message answers to, still takes its entry
    template <typename Message>
    void on(const Message&) {
        ++index;
    }

    template <typename Code>
    void on_unknown(Code, std::span<const std::byte>) {
        ++index;
    }

    void on(const protocol::SystemEventMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.systemeventmessage";
        values[entry + ".payload.systemeventmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.systemeventmessage.eventcode"] = canonical::text(canonical::character(message.event_code()), ' ', false);
        values[entry + ".payload.systemeventmessage.currentyear"] = canonical::number(message.current_year());
        values[entry + ".payload.systemeventmessage.currentmonth"] = canonical::number(message.current_month());
        values[entry + ".payload.systemeventmessage.currentday"] = canonical::number(message.current_day());
        values[entry + ".payload.systemeventmessage.version"] = canonical::number(message.version());
        values[entry + ".payload.systemeventmessage.subversion"] = canonical::number(message.sub_version());
    }

    void on(const protocol::ComplexStrategyDirectoryMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.complexstrategydirectorymessage";
        values[entry + ".payload.complexstrategydirectorymessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.complexstrategydirectorymessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.complexstrategydirectorymessage.strategytype"] = canonical::text(canonical::character(message.strategy_type()), ' ', false);
        values[entry + ".payload.complexstrategydirectorymessage.source"] = canonical::number(message.source());
        values[entry + ".payload.complexstrategydirectorymessage.underlyingsymbol"] = canonical::text(std::string(message.underlying_symbol()), ' ', false);
        values[entry + ".payload.complexstrategydirectorymessage.numberoflegs"] = canonical::number(message.number_of_legs());
    }

    void on(const protocol::StrategyOpenClosedMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.strategyopenclosedmessage";
        values[entry + ".payload.strategyopenclosedmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.strategyopenclosedmessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.strategyopenclosedmessage.openstate"] = canonical::text(canonical::character(message.open_state()), ' ', false);
    }

    void on(const protocol::StrategyTradingActionMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.strategytradingactionmessage";
        values[entry + ".payload.strategytradingactionmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.strategytradingactionmessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.strategytradingactionmessage.currenttradingstate"] = canonical::text(canonical::character(message.current_trading_state()), ' ', false);
    }

    void on(const protocol::StrategyBestBidAndAskUpdate& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidandaskupdate";
        values[entry + ".payload.strategybestbidandaskupdate.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.strategybestbidandaskupdate.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.strategybestbidandaskupdate.quotecondition"] = canonical::text(canonical::character(message.quote_condition()), ' ', false);
        values[entry + ".payload.strategybestbidandaskupdate.bidprice"] = canonical::scaled(message.bid_price().mantissa(), message.bid_price().exponent());
        values[entry + ".payload.strategybestbidandaskupdate.bidsize"] = canonical::number(message.bid_size());
        values[entry + ".payload.strategybestbidandaskupdate.bidcustsize"] = canonical::number(message.bid_cust_size());
        values[entry + ".payload.strategybestbidandaskupdate.bidprocustsize"] = canonical::number(message.bid_pro_cust_size());
        values[entry + ".payload.strategybestbidandaskupdate.bidnttsize"] = canonical::number(message.bid_ntt_size());
        values[entry + ".payload.strategybestbidandaskupdate.bidmarketsize"] = canonical::number(message.bid_market_size());
        values[entry + ".payload.strategybestbidandaskupdate.bidnttmarketsize"] = canonical::number(message.bid_ntt_market_size());
        values[entry + ".payload.strategybestbidandaskupdate.askprice"] = canonical::scaled(message.ask_price().mantissa(), message.ask_price().exponent());
        values[entry + ".payload.strategybestbidandaskupdate.asksize"] = canonical::number(message.ask_size());
        values[entry + ".payload.strategybestbidandaskupdate.askcustsize"] = canonical::number(message.ask_cust_size());
        values[entry + ".payload.strategybestbidandaskupdate.askprocustsize"] = canonical::number(message.ask_pro_cust_size());
        values[entry + ".payload.strategybestbidandaskupdate.asknttsize"] = canonical::number(message.ask_ntt_size());
        values[entry + ".payload.strategybestbidandaskupdate.askmarketsize"] = canonical::number(message.ask_market_size());
        values[entry + ".payload.strategybestbidandaskupdate.asknttmarketsize"] = canonical::number(message.ask_ntt_market_size());
    }

    void on(const protocol::StrategyBestBidUpdate& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.strategybestbidupdate";
        values[entry + ".payload.strategybestbidupdate.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.strategybestbidupdate.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.strategybestbidupdate.quotecondition"] = canonical::text(canonical::character(message.quote_condition()), ' ', false);
        values[entry + ".payload.strategybestbidupdate.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.strategybestbidupdate.size"] = canonical::number(message.size());
        values[entry + ".payload.strategybestbidupdate.custsize"] = canonical::number(message.cust_size());
        values[entry + ".payload.strategybestbidupdate.procustsize"] = canonical::number(message.pro_cust_size());
        values[entry + ".payload.strategybestbidupdate.nttsize"] = canonical::number(message.ntt_size());
        values[entry + ".payload.strategybestbidupdate.marketsize"] = canonical::number(message.market_size());
        values[entry + ".payload.strategybestbidupdate.nttmarketsize"] = canonical::number(message.ntt_market_size());
    }

    void on(const protocol::StrategyBestAskUpdate& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.strategybestaskupdate";
        values[entry + ".payload.strategybestaskupdate.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.strategybestaskupdate.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.strategybestaskupdate.quotecondition"] = canonical::text(canonical::character(message.quote_condition()), ' ', false);
        values[entry + ".payload.strategybestaskupdate.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.strategybestaskupdate.size"] = canonical::number(message.size());
        values[entry + ".payload.strategybestaskupdate.custsize"] = canonical::number(message.cust_size());
        values[entry + ".payload.strategybestaskupdate.procustsize"] = canonical::number(message.pro_cust_size());
        values[entry + ".payload.strategybestaskupdate.nttsize"] = canonical::number(message.ntt_size());
        values[entry + ".payload.strategybestaskupdate.marketsize"] = canonical::number(message.market_size());
        values[entry + ".payload.strategybestaskupdate.nttmarketsize"] = canonical::number(message.ntt_market_size());
    }

    void on(const protocol::ComplexStrategyTickerMessage& message) {
        const std::string entry = "packet.messages.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.messages.message.payload.complexstrategytickermessage";
        values[entry + ".payload.complexstrategytickermessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.complexstrategytickermessage.strategyid"] = canonical::number(message.strategy_id());
        values[entry + ".payload.complexstrategytickermessage.lastprice"] = canonical::scaled(message.last_price().mantissa(), message.last_price().exponent());
        values[entry + ".payload.complexstrategytickermessage.size"] = canonical::number(message.size());
        values[entry + ".payload.complexstrategytickermessage.volume"] = canonical::number(message.volume());
        values[entry + ".payload.complexstrategytickermessage.high"] = canonical::number(message.high());
        values[entry + ".payload.complexstrategytickermessage.low"] = canonical::number(message.low());
        values[entry + ".payload.complexstrategytickermessage.first"] = canonical::number(message.first());
        values[entry + ".payload.complexstrategytickermessage.tradecondition"] = canonical::text(canonical::character(message.trade_condition()), ' ', false);
    }
};

// The values the Flyweight reader reads from one datagram, by indexed address. A datagram it cannot
// read is a value the model never reads, so it fails rather than passing with nothing compared.
canonical::Listing read(const packet::Frame& frame) {
    Reader reader;

    try {
        protocol::PacketReader::read(std::span<const std::byte>(frame.payload, frame.payload_len), reader);
    } catch (const protocol::DecodeError& error) {
        reader.values["(does not decode)"] = error.what();
    }

    return reader.values;
}

// Read each datagram of a sample with Flyweight and hold it to the model's values
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
    std::printf("== Nasdaq.IseOptions.TopComboQuoteFeed.Itch.v1.0 (flyweight values)\n");
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
