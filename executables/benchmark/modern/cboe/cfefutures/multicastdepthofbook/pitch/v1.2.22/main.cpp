// Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/cboe/cfefutures/multicastdepthofbook/pitch/v1.2.22/definitions.hpp"

namespace protocol = ::cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22;

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

        if (iterator.message_type == protocol::TimeReferenceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TimeReferenceMessage::parse(iterator.message);
            checksum += bench::digest(message->midnight_reference.get());
            checksum += bench::digest(message->time_reference.get());
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->trade_date.get());
        } else if (iterator.message_type == protocol::TimeMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TimeMessage::parse(iterator.message);
            checksum += bench::digest(message->time_reference.get());
            checksum += bench::digest(message->epoch_time.get());
        } else if (iterator.message_type == protocol::UnitClearMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::UnitClearMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
        } else if (iterator.message_type == protocol::FuturesInstrumentDefinitionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::FuturesInstrumentDefinitionMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->unit_timestamp.get());
            checksum += bench::digest(message->report_symbol.get());
            checksum += bench::digest(message->futures_flags.Variance());
            checksum += bench::digest(message->expiration_date.get());
            checksum += bench::digest(message->contract_size.get());
            checksum += bench::digest(message->listing_state.get());
            checksum += bench::digest(message->price_increment.integer());
            checksum += bench::digest(message->leg_count.get());
            checksum += bench::digest(message->leg_offset.get());
            checksum += bench::digest(message->reserved_1.get());
            checksum += bench::digest(message->contract_date.get());
        } else if (iterator.message_type == protocol::FuturesVarianceSymbolMappingMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::FuturesVarianceSymbolMappingMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->unit_timestamp.get());
            checksum += bench::digest(message->feed_symbol.get());
            checksum += bench::digest(message->futures_symbol.get());
            checksum += bench::digest(message->accrued_day_variance.integer());
            checksum += bench::digest(message->num_final_returns.get());
            checksum += bench::digest(message->num_elapsed_returns.get());
        } else if (iterator.message_type == protocol::PriceLimitsMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::PriceLimitsMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->upper_price_limit.integer());
            checksum += bench::digest(message->lower_price_limit.integer());
        } else if (iterator.message_type == protocol::AddOrderLongMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderLongMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity_long.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->price_long.integer());
        } else if (iterator.message_type == protocol::AddOrderShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->side_indicator.get());
            checksum += bench::digest(message->quantity_short.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->price_short.integer());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->execution_id.get());
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
        } else if (iterator.message_type == protocol::ModifyOrderShortMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ModifyOrderShortMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity_short.get());
            checksum += bench::digest(message->price_short.integer());
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
        } else if (iterator.message_type == protocol::TransactionBeginMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TransactionBeginMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
        } else if (iterator.message_type == protocol::TransactionEndMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TransactionEndMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
        } else if (iterator.message_type == protocol::TradeBreakMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeBreakMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->execution_id.get());
        } else if (iterator.message_type == protocol::SettlementMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::SettlementMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->settlement_price.integer());
            checksum += bench::digest(message->issue.get());
        } else if (iterator.message_type == protocol::OpenInterestMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OpenInterestMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->open_interest.get());
        } else if (iterator.message_type == protocol::EndOfDaySummaryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::EndOfDaySummaryMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->open_interest.get());
            checksum += bench::digest(message->high_price.integer());
            checksum += bench::digest(message->low_price.integer());
            checksum += bench::digest(message->open_price.integer());
            checksum += bench::digest(message->close_price.integer());
            checksum += bench::digest(message->total_volume.get());
            checksum += bench::digest(message->block_volume.get());
            checksum += bench::digest(message->ecrp_volume.get());
            checksum += bench::digest(message->summary_flags.HighPriceValid());
            checksum += bench::digest(message->summary_flags.HighPriceIsBid());
            checksum += bench::digest(message->summary_flags.LowPriceValid());
            checksum += bench::digest(message->summary_flags.LowPriceIsOffer());
            checksum += bench::digest(message->summary_flags.OpenCloseValid());
        } else if (iterator.message_type == protocol::TradingStatusMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradingStatusMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
            checksum += bench::digest(message->symbol.get());
            checksum += bench::digest(message->reserved_2.get());
            checksum += bench::digest(message->trading_status.get());
            checksum += bench::digest(message->reserved_3.get());
        } else if (iterator.message_type == protocol::EndOfSessionMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::EndOfSessionMessage::parse(iterator.message);
            checksum += bench::digest(message->time_offset.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Cboe.CfeFutures.MulticastDepthOfBook.Pitch.v1.2.22", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
