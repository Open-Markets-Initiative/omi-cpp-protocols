// CixAts.CixAspen.MarketDataFeed.Aspen.v1.4 canonical values, through the Flyweight reader: every value Flyweight reads
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
#include "cpp/binary/flyweight/cixats/cixaspen/marketdatafeed/aspen/v1.4/definitions.hpp"

namespace protocol = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

namespace {

// The handler the reader hands each datagram's views to
struct Reader {
    canonical::Listing values;
    std::size_t index = 0;

    void on(const protocol::Packet& packet) {
        values["packet.packetheader.marketdayidentifier"] = canonical::numeric(std::string(packet.packet_header().market_day_identifier()));
        values["packet.packetheader.feedidentifier"] = canonical::text(canonical::character(packet.packet_header().feed_identifier()));
        values["packet.packetheader.sequence"] = canonical::number(packet.packet_header().sequence());
        values["packet.packetheader.count"] = canonical::number(packet.packet_header().count());
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

    void on(const protocol::MarketEventMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.marketeventmessage";
        values[entry + ".payload.marketeventmessage.reserved2"] = canonical::text(std::string(message.reserved_2()), ' ', false);
        values[entry + ".payload.marketeventmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.marketeventmessage.event"] = canonical::text(canonical::character(message.event()), ' ', false);
    }

    void on(const protocol::SymbolInformationMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.symbolinformationmessage";
        values[entry + ".payload.symbolinformationmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.symbolinformationmessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.symbolinformationmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".payload.symbolinformationmessage.listingmarket"] = canonical::text(canonical::character(message.listing_market()), ' ', false);
        values[entry + ".payload.symbolinformationmessage.boardlotsize"] = canonical::number(message.board_lot_size());
    }

    void on(const protocol::SymbolStateMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.symbolstatemessage";
        values[entry + ".payload.symbolstatemessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.symbolstatemessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.symbolstatemessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".payload.symbolstatemessage.state"] = canonical::text(canonical::character(message.state()), ' ', false);
        values[entry + ".payload.symbolstatemessage.reserved1"] = canonical::text(canonical::character(message.reserved_1()), ' ', false);
        values[entry + ".payload.symbolstatemessage.info"] = canonical::text(std::string(message.info()), ' ', false);
    }

    void on(const protocol::NewOrderAddMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.neworderaddmessage";
        values[entry + ".payload.neworderaddmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.neworderaddmessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.neworderaddmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.neworderaddmessage.side"] = canonical::text(canonical::character(message.side()), ' ', false);
        values[entry + ".payload.neworderaddmessage.quantity"] = canonical::scaled(message.quantity().mantissa(), message.quantity().exponent());
        values[entry + ".payload.neworderaddmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".payload.neworderaddmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.neworderaddmessage.broker"] = canonical::text(std::string(message.broker()), ' ', false);
        values[entry + ".payload.neworderaddmessage.reserved1"] = canonical::text(canonical::character(message.reserved_1()), ' ', false);
    }

    void on(const protocol::OrderPartialCancelMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.orderpartialcancelmessage";
        values[entry + ".payload.orderpartialcancelmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.orderpartialcancelmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.orderpartialcancelmessage.quantitycanceled"] = canonical::scaled(message.quantity_canceled().mantissa(), message.quantity_canceled().exponent());
    }

    void on(const protocol::OrderCancelAllMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.ordercancelallmessage";
        values[entry + ".payload.ordercancelallmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.ordercancelallmessage.orderid"] = canonical::number(message.order_id());
    }

    void on(const protocol::OrderExecutedMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.orderexecutedmessage";
        values[entry + ".payload.orderexecutedmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message.order_id());
        values[entry + ".payload.orderexecutedmessage.quantity"] = canonical::scaled(message.quantity().mantissa(), message.quantity().exponent());
        values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number(message.execution_id());
        values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message.side()), ' ', false);
        values[entry + ".payload.orderexecutedmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.orderexecutedmessage.broker"] = canonical::text(std::string(message.broker()), ' ', false);
        values[entry + ".payload.orderexecutedmessage.contrabroker"] = canonical::text(std::string(message.contra_broker()), ' ', false);
    }

    void on(const protocol::TradeMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.trademessage";
        values[entry + ".payload.trademessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.trademessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.trademessage.reserved8"] = canonical::number(message.reserved_8());
        values[entry + ".payload.trademessage.side"] = canonical::text(canonical::character(message.side()), ' ', false);
        values[entry + ".payload.trademessage.shares"] = canonical::scaled(message.shares().mantissa(), message.shares().exponent());
        values[entry + ".payload.trademessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".payload.trademessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.trademessage.executionid"] = canonical::number(message.execution_id());
        values[entry + ".payload.trademessage.broker"] = canonical::text(std::string(message.broker()), ' ', false);
        values[entry + ".payload.trademessage.contrabroker"] = canonical::text(std::string(message.contra_broker()), ' ', false);
    }

    void on(const protocol::TradeCancelMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.tradecancelmessage";
        values[entry + ".payload.tradecancelmessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.tradecancelmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.tradecancelmessage.reserved8"] = canonical::number(message.reserved_8());
        values[entry + ".payload.tradecancelmessage.reserved1"] = canonical::text(canonical::character(message.reserved_1()), ' ', false);
        values[entry + ".payload.tradecancelmessage.shares"] = canonical::scaled(message.shares().mantissa(), message.shares().exponent());
        values[entry + ".payload.tradecancelmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".payload.tradecancelmessage.price"] = canonical::scaled(message.price().mantissa(), message.price().exponent());
        values[entry + ".payload.tradecancelmessage.executionid"] = canonical::number(message.execution_id());
        values[entry + ".payload.tradecancelmessage.broker"] = canonical::text(std::string(message.broker()), ' ', false);
        values[entry + ".payload.tradecancelmessage.contrabroker"] = canonical::text(std::string(message.contra_broker()), ' ', false);
    }

    void on(const protocol::TradeCorrectMessage& message) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".payload"] = "packet.message.payload.tradecorrectmessage";
        values[entry + ".payload.tradecorrectmessage.symbolid"] = canonical::number(message.symbol_id());
        values[entry + ".payload.tradecorrectmessage.timestamp"] = canonical::number(message.timestamp());
        values[entry + ".payload.tradecorrectmessage.reserved8"] = canonical::number(message.reserved_8());
        values[entry + ".payload.tradecorrectmessage.reserved1"] = canonical::text(canonical::character(message.reserved_1()), ' ', false);
        values[entry + ".payload.tradecorrectmessage.symbol"] = canonical::text(std::string(message.symbol()), ' ', false);
        values[entry + ".payload.tradecorrectmessage.executionid"] = canonical::number(message.execution_id());
        values[entry + ".payload.tradecorrectmessage.broker"] = canonical::text(std::string(message.broker()), ' ', false);
        values[entry + ".payload.tradecorrectmessage.contrabroker"] = canonical::text(std::string(message.contra_broker()), ' ', false);
        values[entry + ".payload.tradecorrectmessage.originalexecutionid"] = canonical::number(message.original_execution_id());
        values[entry + ".payload.tradecorrectmessage.originaltradeprice"] = canonical::scaled(message.original_trade_price().mantissa(), message.original_trade_price().exponent());
        values[entry + ".payload.tradecorrectmessage.originaltradequantity"] = canonical::scaled(message.original_trade_quantity().mantissa(), message.original_trade_quantity().exponent());
        values[entry + ".payload.tradecorrectmessage.correctedtradeprice"] = canonical::scaled(message.corrected_trade_price().mantissa(), message.corrected_trade_price().exponent());
        values[entry + ".payload.tradecorrectmessage.correctedtradequantity"] = canonical::scaled(message.corrected_trade_quantity().mantissa(), message.corrected_trade_quantity().exponent());
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
    std::printf("== CixAts.CixAspen.MarketDataFeed.Aspen.v1.4 (flyweight values)\n");
    int failures = 0;
    failures += check("MarketEventMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/MarketEventMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/MarketEventMessage.values");
    failures += check("NewOrderAddMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/NewOrderAddMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/NewOrderAddMessage.values");
    failures += check("OrderCancelAllMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/OrderCancelAllMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/OrderCancelAllMessage.values");
    failures += check("OrderExecutedMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/OrderExecutedMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/OrderExecutedMessage.values");
    failures += check("OrderPartialCancelMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/OrderPartialCancelMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/OrderPartialCancelMessage.values");
    failures += check("SymbolInformationMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/SymbolInformationMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/SymbolInformationMessage.values");
    failures += check("SymbolStateMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/SymbolStateMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/SymbolStateMessage.values");
    failures += check("TradeMessage", "CixAts/CixAspen.MarketDataFeed.Aspen.v1.4/TradeMessage.pcap", "cixats/cixaspen/marketdatafeed/aspen/v1.4/TradeMessage.values");
    return failures == 0 ? 0 : 1;
}
