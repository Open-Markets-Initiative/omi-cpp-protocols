// Cboe.C1Options.MulticastDepthOfBook.Pitch.v2.39.4 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/c1options/multicastdepthofbook/pitch/v2.39.4.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/cboe/c1options/multicastdepthofbook/pitch/v2.39.4/definitions.hpp"

namespace protocol = ::cboe::c1options::multicastdepthofbook::pitch::v2_39_4;

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
            checksum += bench::digest(message->long_quantity.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->long_price.integer());
            checksum += bench::digest(message->add_flags.Display());
        } else if (iterator.message_type == protocol::AddOrderShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->short_quantity.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->short_price.integer());
            checksum += bench::digest(message->add_flags.Display());
        } else if (iterator.message_type == protocol::AddOrderExpandedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderExpandedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->long_quantity.get());
            checksum += bench::digest(message->expanded_symbol.get());
            checksum += bench::digest(message->long_price.integer());
            checksum += bench::digest(message->add_flags.Display());
            checksum += bench::digest(message->participant_id.get());
            checksum += bench::digest(message->customer_indicator.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->trade_condition.get());
        } else if (iterator.message_type == protocol::OrderExecutedAtPriceSizeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedAtPriceSizeMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->remaining_quantity.get());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->long_price.integer());
            checksum += bench::digest(message->trade_condition.get());
        } else if (iterator.message_type == protocol::ReduceSizeLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ReduceSizeLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->canceled_long_quantity.get());
        } else if (iterator.message_type == protocol::ReduceSizeShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ReduceSizeShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->canceled_short_quantity.get());
        } else if (iterator.message_type == protocol::ModifyOrderLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ModifyOrderLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->long_quantity.get());
            checksum += bench::digest(message->long_price.integer());
            checksum += bench::digest(message->modify_flags.Display());
            checksum += bench::digest(message->modify_flags.MaintainPriority());
        } else if (iterator.message_type == protocol::ModifyOrderShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ModifyOrderShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->short_quantity.get());
            checksum += bench::digest(message->short_price.integer());
            checksum += bench::digest(message->modify_flags.Display());
            checksum += bench::digest(message->modify_flags.MaintainPriority());
        } else if (iterator.message_type == protocol::DeleteOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::DeleteOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
        } else if (iterator.message_type == protocol::TradeLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->long_quantity.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->long_price.integer());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->trade_condition.get());
        } else if (iterator.message_type == protocol::TradeShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->short_quantity.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->short_price.integer());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->trade_condition.get());
        } else if (iterator.message_type == protocol::TradeExpandedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeExpandedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->long_quantity.get());
            checksum += bench::digest(message->expanded_symbol.get());
            checksum += bench::digest(message->long_price.integer());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->trade_condition.get());
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->execution_id.get());
        } else if (iterator.message_type == protocol::EndOfSessionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::EndOfSessionMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
        } else if (iterator.message_type == protocol::SymbolMappingMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SymbolMappingMessage::parse(iterator.message);
            checksum += bench::digest(message->feed_symbol.get());
            checksum += bench::digest(message->osi_symbol.get());
            checksum += bench::digest(message->symbol_condition.get());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->expanded_symbol.get());
            checksum += bench::digest(message->trading_status.get());
            checksum += bench::digest(message->reg_sho_action.get());
        } else if (iterator.message_type == protocol::AuctionUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->stock_symbol.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->reference_price.integer());
            checksum += bench::digest(message->buy_shares.get());
            checksum += bench::digest(message->sell_shares.get());
            checksum += bench::digest(message->indicative_price.integer());
            checksum += bench::digest(message->auction_only_price.integer());
        } else if (iterator.message_type == protocol::AuctionSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->stock_symbol.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->long_price.integer());
            checksum += bench::digest(message->shares.get());
        } else if (iterator.message_type == protocol::AuctionNotificationMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionNotificationMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->auction_id.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->long_price.integer());
            checksum += bench::digest(message->contracts.get());
            checksum += bench::digest(message->customer_indicator.get());
            checksum += bench::digest(message->participant_id.get());
            checksum += bench::digest(message->auction_end_offset.get());
        } else if (iterator.message_type == protocol::AuctionCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->auction_id.get());
        } else if (iterator.message_type == protocol::AuctionTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->auction_id.get());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->long_price.integer());
            checksum += bench::digest(message->contracts.get());
        } else if (iterator.message_type == protocol::RetailPriceImprovementMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RetailPriceImprovementMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->expanded_symbol.get());
            checksum += bench::digest(message->retail_price_improvement.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cboe.C1Options.MulticastDepthOfBook.Pitch.v2.39.4", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
