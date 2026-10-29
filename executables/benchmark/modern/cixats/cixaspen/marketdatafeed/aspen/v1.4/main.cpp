// CixAts.CixAspen.MarketDataFeed.Aspen.v1.4 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/cixats/cixaspen/marketdatafeed/aspen/v1.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

#include <cstdio>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <string>
#include <utility>
#include <vector>

#include "PcapIterator.hpp"
#include "Frame.hpp"
#include "executables/benchmark/Benchmark.hpp"
#include "cpp/binary/modern/cixats/cixaspen/marketdatafeed/aspen/v1.4/definitions.hpp"

namespace protocol = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->market_day_identifier.get());
    checksum += bench::digest(iterator.packet_header->feed_identifier.get());
    checksum += bench::digest(iterator.packet_header->sequence.get());
    checksum += bench::digest(iterator.packet_header->count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::MarketEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MarketEventMessage::parse(iterator.message);
            checksum += bench::digest(message->reserved_2.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->event.get());
        } else if (iterator.message_type == protocol::SymbolInformationMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SymbolInformationMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol_id.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->listing_market.get());
            checksum += bench::digest(message->board_lot_size.get());
        } else if (iterator.message_type == protocol::SymbolStateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SymbolStateMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol_id.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->state.get());
            checksum += bench::digest(message->reserved_1.get());
            checksum += bench::digest(message->info.get());
        } else if (iterator.message_type == protocol::NewOrderAddMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::NewOrderAddMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->symbol_id.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->quantity.integer());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->broker.get());
            checksum += bench::digest(message->reserved_1.get());
        } else if (iterator.message_type == protocol::OrderPartialCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderPartialCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity_canceled.integer());
        } else if (iterator.message_type == protocol::OrderCancelAllMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderCancelAllMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity.integer());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->broker.get());
            checksum += bench::digest(message->contra_broker.get());
        } else if (iterator.message_type == protocol::TradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol_id.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->reserved_8.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->shares.integer());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->broker.get());
            checksum += bench::digest(message->contra_broker.get());
        } else if (iterator.message_type == protocol::TradeCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol_id.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->reserved_8.get());
            checksum += bench::digest(message->reserved_1.get());
            checksum += bench::digest(message->shares.integer());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->broker.get());
            checksum += bench::digest(message->contra_broker.get());
        } else if (iterator.message_type == protocol::TradeCorrectMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeCorrectMessage::parse(iterator.message);
            checksum += bench::digest(message->symbol_id.get());
            checksum += bench::digest(message->timestamp.get());
            checksum += bench::digest(message->reserved_8.get());
            checksum += bench::digest(message->reserved_1.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->broker.get());
            checksum += bench::digest(message->contra_broker.get());
            checksum += bench::digest(message->original_execution_id.get());
            checksum += bench::digest(message->original_trade_price.integer());
            checksum += bench::digest(message->original_trade_quantity.integer());
            checksum += bench::digest(message->corrected_trade_price.integer());
            checksum += bench::digest(message->corrected_trade_quantity.integer());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("CixAts.CixAspen.MarketDataFeed.Aspen.v1.4", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
