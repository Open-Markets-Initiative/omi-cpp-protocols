// Jnx.JnxEquities.Pts.Itch.v1.6 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/jnx/jnxequities/pts/itch/v1.6.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/jnx/jnxequities/pts/itch/v1.6/definitions.hpp"

namespace protocol = ::jnx::jnxequities::pts::itch::v1_6;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->session.get());
    checksum += bench::digest(iterator.packet_header->sequence_number.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::SecondsMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SecondsMessage::parse(iterator.message);
            checksum += bench::digest(message->seconds.get());
        } else if (iterator.message_type == protocol::SystemEventMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SystemEventMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->group.get());
            checksum += bench::digest(message->system_event.get());
        } else if (iterator.message_type == protocol::PriceTickSizeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::PriceTickSizeMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->price_tick_size_table_id.get());
            checksum += bench::digest(message->price_tick_size.integer());
            checksum += bench::digest(message->price_start.integer());
        } else if (iterator.message_type == protocol::OrderbookDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderbookDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->orderbook_id.get());
            checksum += bench::digest(message->orderbook_code.get());
            checksum += bench::digest(message->group.get());
            checksum += bench::digest(message->round_lot_size.get());
            checksum += bench::digest(message->price_tick_size_table_id.get());
            checksum += bench::digest(message->price_decimals.get());
            checksum += bench::digest(message->upper_price_limit.integer());
            checksum += bench::digest(message->lower_price_limit.integer());
        } else if (iterator.message_type == protocol::TradingStateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingStateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->orderbook_id.get());
            checksum += bench::digest(message->group.get());
            checksum += bench::digest(message->trading_state.get());
        } else if (iterator.message_type == protocol::ShortSellingPriceRestrictionStateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ShortSellingPriceRestrictionStateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->orderbook_id.get());
            checksum += bench::digest(message->group.get());
            checksum += bench::digest(message->short_selling_state.get());
        } else if (iterator.message_type == protocol::OrderAddedWithoutAttributesMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderAddedWithoutAttributesMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_number.get());
            checksum += bench::digest(message->buy_sell_indicator.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->orderbook_id.get());
            checksum += bench::digest(message->group.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::OrderAddedWithAttributesMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderAddedWithAttributesMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_number.get());
            checksum += bench::digest(message->buy_sell_indicator.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->orderbook_id.get());
            checksum += bench::digest(message->group.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->attribution.get());
            checksum += bench::digest(message->order_type.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_number.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->match_number.get());
        } else if (iterator.message_type == protocol::OrderDeletedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeletedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->order_number.get());
        } else if (iterator.message_type == protocol::OrderReplacedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderReplacedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->original_order_number.get());
            checksum += bench::digest(message->new_order_number.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.integer());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Jnx.JnxEquities.Pts.Itch.v1.6", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
