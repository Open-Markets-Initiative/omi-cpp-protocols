// CixAts.CixAspen.MarketDataFeed.Aspen.v1.4 canonical values, through the Modern iterator: every value Modern reads from
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
#include "cpp/binary/modern/cixats/cixaspen/marketdatafeed/aspen/v1.4/definitions.hpp"

namespace protocol = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

namespace {

// The values the Modern iterator reads from one datagram, by indexed address
canonical::Listing read(const packet::Frame& frame) {
    canonical::Listing values;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    values["packet.packetheader.marketdayidentifier"] = canonical::numeric(std::string(iterator.packet_header->market_day_identifier.get()));
    values["packet.packetheader.feedidentifier"] = canonical::text(canonical::character(iterator.packet_header->feed_identifier.get()));
    values["packet.packetheader.sequence"] = canonical::number(iterator.packet_header->sequence.get());
    values["packet.packetheader.count"] = canonical::number(iterator.packet_header->count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        const std::string entry = "packet.message[" + std::to_string(index++) + "]";
        values[entry + ".messageheader.length"] = canonical::number(iterator.message_header->length.get());
        values[entry + ".messageheader.messagetype"] = canonical::text(canonical::character(iterator.message_header->message_type.get()));

        if (iterator.message_type == protocol::MarketEventMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.marketeventmessage";
            [[maybe_unused]] const auto* message = protocol::MarketEventMessage::parse(iterator.message);
            values[entry + ".payload.marketeventmessage.reserved2"] = canonical::text(std::string(message->reserved_2.get()), ' ', false);
            values[entry + ".payload.marketeventmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.marketeventmessage.event"] = canonical::text(canonical::character(message->event.get()), ' ', false);
        } else if (iterator.message_type == protocol::SymbolInformationMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.symbolinformationmessage";
            [[maybe_unused]] const auto* message = protocol::SymbolInformationMessage::parse(iterator.message);
            values[entry + ".payload.symbolinformationmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.symbolinformationmessage.symbolid"] = canonical::number(message->symbol_id.get());
            values[entry + ".payload.symbolinformationmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".payload.symbolinformationmessage.listingmarket"] = canonical::text(canonical::character(message->listing_market.get()), ' ', false);
            values[entry + ".payload.symbolinformationmessage.boardlotsize"] = canonical::number(message->board_lot_size.get());
        } else if (iterator.message_type == protocol::SymbolStateMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.symbolstatemessage";
            [[maybe_unused]] const auto* message = protocol::SymbolStateMessage::parse(iterator.message);
            values[entry + ".payload.symbolstatemessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.symbolstatemessage.symbolid"] = canonical::number(message->symbol_id.get());
            values[entry + ".payload.symbolstatemessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".payload.symbolstatemessage.state"] = canonical::text(canonical::character(message->state.get()), ' ', false);
            values[entry + ".payload.symbolstatemessage.reserved1"] = canonical::text(canonical::character(message->reserved_1.get()), ' ', false);
            values[entry + ".payload.symbolstatemessage.info"] = canonical::text(std::string(message->info.get()), ' ', false);
        } else if (iterator.message_type == protocol::NewOrderAddMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.neworderaddmessage";
            [[maybe_unused]] const auto* message = protocol::NewOrderAddMessage::parse(iterator.message);
            values[entry + ".payload.neworderaddmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.neworderaddmessage.symbolid"] = canonical::number(message->symbol_id.get());
            values[entry + ".payload.neworderaddmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.neworderaddmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.neworderaddmessage.quantity"] = canonical::scaled(message->quantity.integer(), -6);
            values[entry + ".payload.neworderaddmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".payload.neworderaddmessage.price"] = canonical::scaled(message->price.integer(), -6);
            values[entry + ".payload.neworderaddmessage.broker"] = canonical::text(std::string(message->broker.get()), ' ', false);
            values[entry + ".payload.neworderaddmessage.reserved1"] = canonical::text(canonical::character(message->reserved_1.get()), ' ', false);
        } else if (iterator.message_type == protocol::OrderPartialCancelMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.orderpartialcancelmessage";
            [[maybe_unused]] const auto* message = protocol::OrderPartialCancelMessage::parse(iterator.message);
            values[entry + ".payload.orderpartialcancelmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.orderpartialcancelmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderpartialcancelmessage.quantitycanceled"] = canonical::scaled(message->quantity_canceled.integer(), -6);
        } else if (iterator.message_type == protocol::OrderCancelAllMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.ordercancelallmessage";
            [[maybe_unused]] const auto* message = protocol::OrderCancelAllMessage::parse(iterator.message);
            values[entry + ".payload.ordercancelallmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.ordercancelallmessage.orderid"] = canonical::number(message->order_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.orderexecutedmessage";
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            values[entry + ".payload.orderexecutedmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.orderexecutedmessage.orderid"] = canonical::number(message->order_id.get());
            values[entry + ".payload.orderexecutedmessage.quantity"] = canonical::scaled(message->quantity.integer(), -6);
            values[entry + ".payload.orderexecutedmessage.executionid"] = canonical::number(message->execution_id.get());
            values[entry + ".payload.orderexecutedmessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.orderexecutedmessage.price"] = canonical::scaled(message->price.integer(), -6);
            values[entry + ".payload.orderexecutedmessage.broker"] = canonical::text(std::string(message->broker.get()), ' ', false);
            values[entry + ".payload.orderexecutedmessage.contrabroker"] = canonical::text(std::string(message->contra_broker.get()), ' ', false);
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.trademessage";
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            values[entry + ".payload.trademessage.symbolid"] = canonical::number(message->symbol_id.get());
            values[entry + ".payload.trademessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.trademessage.reserved8"] = canonical::number(message->reserved_8.get());
            values[entry + ".payload.trademessage.side"] = canonical::text(canonical::character(message->side.get()), ' ', false);
            values[entry + ".payload.trademessage.shares"] = canonical::scaled(message->shares.integer(), -6);
            values[entry + ".payload.trademessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".payload.trademessage.price"] = canonical::scaled(message->price.integer(), -6);
            values[entry + ".payload.trademessage.executionid"] = canonical::number(message->execution_id.get());
            values[entry + ".payload.trademessage.broker"] = canonical::text(std::string(message->broker.get()), ' ', false);
            values[entry + ".payload.trademessage.contrabroker"] = canonical::text(std::string(message->contra_broker.get()), ' ', false);
        } else if (iterator.message_type == protocol::TradeCancelMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.tradecancelmessage";
            [[maybe_unused]] const auto* message = protocol::TradeCancelMessage::parse(iterator.message);
            values[entry + ".payload.tradecancelmessage.symbolid"] = canonical::number(message->symbol_id.get());
            values[entry + ".payload.tradecancelmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.tradecancelmessage.reserved8"] = canonical::number(message->reserved_8.get());
            values[entry + ".payload.tradecancelmessage.reserved1"] = canonical::text(canonical::character(message->reserved_1.get()), ' ', false);
            values[entry + ".payload.tradecancelmessage.shares"] = canonical::scaled(message->shares.integer(), -6);
            values[entry + ".payload.tradecancelmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".payload.tradecancelmessage.price"] = canonical::scaled(message->price.integer(), -6);
            values[entry + ".payload.tradecancelmessage.executionid"] = canonical::number(message->execution_id.get());
            values[entry + ".payload.tradecancelmessage.broker"] = canonical::text(std::string(message->broker.get()), ' ', false);
            values[entry + ".payload.tradecancelmessage.contrabroker"] = canonical::text(std::string(message->contra_broker.get()), ' ', false);
        } else if (iterator.message_type == protocol::TradeCorrectMessage::message_type) {
            values[entry + ".payload"] = "packet.message.payload.tradecorrectmessage";
            [[maybe_unused]] const auto* message = protocol::TradeCorrectMessage::parse(iterator.message);
            values[entry + ".payload.tradecorrectmessage.symbolid"] = canonical::number(message->symbol_id.get());
            values[entry + ".payload.tradecorrectmessage.timestamp"] = canonical::number(message->timestamp.get());
            values[entry + ".payload.tradecorrectmessage.reserved8"] = canonical::number(message->reserved_8.get());
            values[entry + ".payload.tradecorrectmessage.reserved1"] = canonical::text(canonical::character(message->reserved_1.get()), ' ', false);
            values[entry + ".payload.tradecorrectmessage.symbol"] = canonical::text(std::string(message->symbol.get()), ' ', false);
            values[entry + ".payload.tradecorrectmessage.executionid"] = canonical::number(message->execution_id.get());
            values[entry + ".payload.tradecorrectmessage.broker"] = canonical::text(std::string(message->broker.get()), ' ', false);
            values[entry + ".payload.tradecorrectmessage.contrabroker"] = canonical::text(std::string(message->contra_broker.get()), ' ', false);
            values[entry + ".payload.tradecorrectmessage.originalexecutionid"] = canonical::number(message->original_execution_id.get());
            values[entry + ".payload.tradecorrectmessage.originaltradeprice"] = canonical::scaled(message->original_trade_price.integer(), -6);
            values[entry + ".payload.tradecorrectmessage.originaltradequantity"] = canonical::scaled(message->original_trade_quantity.integer(), -6);
            values[entry + ".payload.tradecorrectmessage.correctedtradeprice"] = canonical::scaled(message->corrected_trade_price.integer(), -6);
            values[entry + ".payload.tradecorrectmessage.correctedtradequantity"] = canonical::scaled(message->corrected_trade_quantity.integer(), -6);
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
    std::printf("== CixAts.CixAspen.MarketDataFeed.Aspen.v1.4 (modern values)\n");
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
