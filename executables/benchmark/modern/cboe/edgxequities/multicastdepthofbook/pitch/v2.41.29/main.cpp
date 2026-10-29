// Cboe.EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/cboe/edgxequities/multicastdepthofbook/pitch/v2.41.29/definitions.hpp"

namespace protocol = ::cboe::edgxequities::multicastdepthofbook::pitch::v2_41_29;

namespace {

// The values the Modern iterator reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::MessageIterator iterator;
    iterator.initialize(frame.payload, frame.payload_len);

    checksum += bench::digest(iterator.packet_header->length.get());
    checksum += bench::digest(iterator.packet_header->message_count.get());
    checksum += bench::digest(iterator.packet_header->unit.get());
    checksum += bench::digest(iterator.packet_header->sequence.get());

    std::size_t index = 0;

    while (iterator.next()) {
        checksum += index++;
        checksum += bench::digest(iterator.message_header->message_length.get());
        checksum += bench::digest(iterator.message_header->message_type.get());

        if (iterator.message_type == protocol::TimeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TimeMessage::parse(iterator.message);
            checksum += bench::digest(message->time.get());
        } else if (iterator.message_type == protocol::UnitClearMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::UnitClearMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
        } else if (iterator.message_type == protocol::AddOrderLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->symbol_short.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->add_order_flags.Display());
        } else if (iterator.message_type == protocol::AddOrderShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity_short.get());
            checksum += bench::digest(message->symbol_short.get());
            checksum += bench::digest(message->price_short.integer());
            checksum += bench::digest(message->add_order_flags.Display());
        } else if (iterator.message_type == protocol::AddOrderExpandedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderExpandedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->symbol_long.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->add_order_flags.Display());
            checksum += bench::digest(message->participant_id.get());
            checksum += bench::digest(message->customer_indicator.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->execution_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedAtPriceSizeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedAtPriceSizeMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->remaining_quantity.get());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::ReduceSizeLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ReduceSizeLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->canceled_quantity.get());
        } else if (iterator.message_type == protocol::ReduceSizeShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ReduceSizeShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->canceled_quantity_short.get());
        } else if (iterator.message_type == protocol::ModifyOrderLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ModifyOrderLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->modify_order_flags.Display());
            checksum += bench::digest(message->modify_order_flags.Priority());
        } else if (iterator.message_type == protocol::ModifyOrderShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ModifyOrderShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity_short.get());
            checksum += bench::digest(message->price_short.integer());
            checksum += bench::digest(message->modify_order_flags.Display());
            checksum += bench::digest(message->modify_order_flags.Priority());
        } else if (iterator.message_type == protocol::DeleteOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::DeleteOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
        } else if (iterator.message_type == protocol::TradeLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->symbol_short.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->execution_id.get());
        } else if (iterator.message_type == protocol::TradeShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity_short.get());
            checksum += bench::digest(message->symbol_short.get());
            checksum += bench::digest(message->price_short.integer());
            checksum += bench::digest(message->execution_id.get());
        } else if (iterator.message_type == protocol::TradeExpandedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeExpandedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->symbol_long.get());
            checksum += bench::digest(message->price.integer());
            checksum += bench::digest(message->execution_id.get());
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->execution_id.get());
        } else if (iterator.message_type == protocol::EndOfSession::message_type) {
            [[maybe_unused]] const auto* message = protocol::EndOfSession::parse(iterator.message);
            checksum += bench::digest(message->last_timestamp.get());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol_long.get());
            checksum += bench::digest(message->trading_status.get());
            checksum += bench::digest(message->reg_sho_action.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cboe.EdgxEquities.MulticastDepthOfBook.Pitch.v2.41.29", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
