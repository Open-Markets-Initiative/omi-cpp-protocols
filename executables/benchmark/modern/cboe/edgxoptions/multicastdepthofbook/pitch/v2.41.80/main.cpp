// Cboe.EdgxOptions.MulticastDepthOfBook.Pitch.v2.41.80 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/cboe/edgxoptions/multicastdepthofbook/pitch/v2.41.80/definitions.hpp"

namespace protocol = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

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
        } else if (iterator.message_type == protocol::TransactionBeginMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TransactionBeginMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
        } else if (iterator.message_type == protocol::TransactionEndMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TransactionEndMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
        } else if (iterator.message_type == protocol::AddOrderLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity_long.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->add_flags.Aon());
        } else if (iterator.message_type == protocol::AddOrderShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity_short.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->price_short.integer());
            checksum += bench::digest(message->add_flags.Aon());
        } else if (iterator.message_type == protocol::AddOrderExpandedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderExpandedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity_long.get());
            checksum += bench::digest(message->expanded_symbol.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->add_flags.Aon());
            checksum += bench::digest(message->participant_id.get());
            checksum += bench::digest(message->customer_indicator.get());
            checksum += bench::digest(message->client_id.get());
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
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->trade_condition.get());
        } else if (iterator.message_type == protocol::ReduceSizeLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ReduceSizeLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->canceled_quantity_long.get());
        } else if (iterator.message_type == protocol::ReduceSizeShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ReduceSizeShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->canceled_quantity_short.get());
        } else if (iterator.message_type == protocol::ModifyOrderLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ModifyOrderLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity_long.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->modify_flags.Display());
            checksum += bench::digest(message->modify_flags.MaintainPriority());
        } else if (iterator.message_type == protocol::ModifyOrderShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ModifyOrderShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity_short.get());
            checksum += bench::digest(message->price_short.integer());
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
            checksum += bench::digest(message->quantity_long.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->trade_condition.get());
        } else if (iterator.message_type == protocol::TradeShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity_short.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->price_short.integer());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->trade_condition.get());
        } else if (iterator.message_type == protocol::TradeExpandedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeExpandedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity_long.get());
            checksum += bench::digest(message->expanded_symbol.get());
            checksum += bench::digest(message->price_long.integer());
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
            checksum += bench::digest(message->underlying.get());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->trading_status.get());
            checksum += bench::digest(message->gth_trading_status.get());
        } else if (iterator.message_type == protocol::WidthUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::WidthUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->underlying.get());
            checksum += bench::digest(message->width_type.get());
            checksum += bench::digest(message->multiplier.integer());
        } else if (iterator.message_type == protocol::OptionsAuctionUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OptionsAuctionUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->expanded_symbol.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->reference_price.integer());
            checksum += bench::digest(message->buy_contracts.get());
            checksum += bench::digest(message->sell_contracts.get());
            checksum += bench::digest(message->indicative_price.integer());
            checksum += bench::digest(message->auction_only_price.integer());
            checksum += bench::digest(message->opening_condition.get());
            checksum += bench::digest(message->composite_market_bid_price.integer());
            checksum += bench::digest(message->composite_market_offer_price.integer());
        } else if (iterator.message_type == protocol::AuctionSummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionSummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->stock_symbol.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->shares_contracts.get());
        } else if (iterator.message_type == protocol::AuctionNotificationMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionNotificationMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->auction_id.get());
            checksum += bench::digest(message->auction_type.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->contracts.get());
            checksum += bench::digest(message->customer_indicator.get());
            checksum += bench::digest(message->participant_id.get());
            checksum += bench::digest(message->auction_end_offset.get());
            checksum += bench::digest(message->client_id.get());
        } else if (iterator.message_type == protocol::AuctionCancelMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionCancelMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->auction_id.get());
        } else if (iterator.message_type == protocol::AuctionTradeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionTradeMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->auction_id.get());
            checksum += bench::digest(message->execution_id.get());
            checksum += bench::digest(message->price_long.integer());
            checksum += bench::digest(message->contracts.get());
        } else if (iterator.message_type == protocol::SoqStrikeRangeUpdateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SoqStrikeRangeUpdateMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->soq_identifier.get());
            checksum += bench::digest(message->lower_strike_price.integer());
            checksum += bench::digest(message->upper_strike_price.integer());
        } else if (iterator.message_type == protocol::ConstituentSymbolMappingMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ConstituentSymbolMappingMessage::parse(iterator.message);
            checksum += bench::digest(message->feed_symbol.get());
            checksum += bench::digest(message->osi_symbol.get());
            checksum += bench::digest(message->symbol_condition.get());
            checksum += bench::digest(message->underlying.get());
            checksum += bench::digest(message->soq_identifier.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cboe.EdgxOptions.MulticastDepthOfBook.Pitch.v2.41.80", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
