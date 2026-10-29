// Asx.AsxDerivatives.Ntp.Itch.v1.05 benchmark, through the Modern iterator: every value it reads from every message of the simulated
// sequence (tests/simulated/asx/asxderivatives/ntp/itch/v1.05.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/modern/asx/asxderivatives/ntp/itch/v1.05/definitions.hpp"

namespace protocol = ::asx::asxderivatives::ntp::itch::v1_05;

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
            checksum += bench::digest(message->second.get());
        } else if (iterator.message_type == protocol::EndOfBusinessTradeDateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::EndOfBusinessTradeDateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->event_code.get());
        } else if (iterator.message_type == protocol::FutureSymbolDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::FutureSymbolDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->symbol_name.get());
            checksum += bench::digest(message->long_name.get());
            checksum += bench::digest(message->isin.get());
            checksum += bench::digest(message->exchange.get());
            checksum += bench::digest(message->instrument.get());
            checksum += bench::digest(message->cfi_code.get());
            checksum += bench::digest(message->expiry_year.get());
            checksum += bench::digest(message->expiry_month.get());
            checksum += bench::digest(message->price_display_decimals.get());
            checksum += bench::digest(message->price_fractional_denominator.get());
            checksum += bench::digest(message->price_minimum_tick.get());
            checksum += bench::digest(message->last_trading_date.get());
            checksum += bench::digest(message->prior_day_settlement.integer());
            checksum += bench::digest(message->currency.get());
            checksum += bench::digest(message->lot_size_or_face_value.get());
            checksum += bench::digest(message->maturity_value.get());
            checksum += bench::digest(message->coupon_rate.get());
            checksum += bench::digest(message->payments_per_year.get());
            checksum += bench::digest(message->block_lot_size.get());
            checksum += bench::digest(message->expiry_date.get());
        } else if (iterator.message_type == protocol::OptionsSymbolDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OptionsSymbolDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->symbol_name.get());
            checksum += bench::digest(message->long_name.get());
            checksum += bench::digest(message->isin.get());
            checksum += bench::digest(message->exchange.get());
            checksum += bench::digest(message->instrument.get());
            checksum += bench::digest(message->cfi_code.get());
            checksum += bench::digest(message->expiry_year.get());
            checksum += bench::digest(message->expiry_month.get());
            checksum += bench::digest(message->option_type.get());
            checksum += bench::digest(message->strike.integer());
            checksum += bench::digest(message->underlying_tradeable_instrument_id.get());
            checksum += bench::digest(message->price_display_decimals.get());
            checksum += bench::digest(message->price_fractional_denominator.get());
            checksum += bench::digest(message->price_minimum_tick.get());
            checksum += bench::digest(message->strike_price_decimal_position.get());
            checksum += bench::digest(message->strike_price_fractional_denominator.get());
            checksum += bench::digest(message->strike_price_minimum_tick.get());
            checksum += bench::digest(message->last_trading_date.get());
            checksum += bench::digest(message->prior_day_settlement.integer());
            checksum += bench::digest(message->volatility.get());
            checksum += bench::digest(message->currency.get());
            checksum += bench::digest(message->lot_size_or_face_value.get());
            checksum += bench::digest(message->maturity_value.get());
            checksum += bench::digest(message->coupon_rate.get());
            checksum += bench::digest(message->payments_per_year.get());
            checksum += bench::digest(message->block_lot_size.get());
            checksum += bench::digest(message->expiry_date.get());
            checksum += bench::digest(message->basis_of_quotation.get());
        } else if (iterator.message_type == protocol::CombinationSymbolDirectoryMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CombinationSymbolDirectoryMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->symbol_name.get());
            checksum += bench::digest(message->long_name.get());
            checksum += bench::digest(message->cfi_code.get());
            checksum += bench::digest(message->price_method.get());
            checksum += bench::digest(message->price_display_decimals.get());
            checksum += bench::digest(message->price_fractional_denominator.get());
            checksum += bench::digest(message->price_minimum_tick.get());
            checksum += bench::digest(message->legs.get());
        } else if (iterator.message_type == protocol::BundlesSymbolDirectory::message_type) {
            [[maybe_unused]] const auto* message = protocol::BundlesSymbolDirectory::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->symbol_name.get());
            checksum += bench::digest(message->long_name.get());
            checksum += bench::digest(message->cfi_code.get());
            checksum += bench::digest(message->price_method.get());
            checksum += bench::digest(message->price_display_decimals.get());
            checksum += bench::digest(message->price_fractional_denominator.get());
            checksum += bench::digest(message->price_minimum_tick.get());
            checksum += bench::digest(message->legs.get());
        } else if (iterator.message_type == protocol::OrderBookStateMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderBookStateMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->session_state.get());
        } else if (iterator.message_type == protocol::AddOrderMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AddOrderMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_book_priority.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::OrderVolumeCancelledMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderVolumeCancelledMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity.get());
        } else if (iterator.message_type == protocol::OrderDeletedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderDeletedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_id.get());
        } else if (iterator.message_type == protocol::OrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity_remaining.get());
            checksum += bench::digest(message->trade_type.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->trade_price.integer());
            checksum += bench::digest(message->combination_trade_id.get());
            checksum += bench::digest(message->counter_party_id.get());
        } else if (iterator.message_type == protocol::AuctionOrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AuctionOrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity_remaining.get());
            checksum += bench::digest(message->trade_type.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->trade_price.integer());
            checksum += bench::digest(message->opposite_order_id.get());
        } else if (iterator.message_type == protocol::CombinationOrderExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CombinationOrderExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->quantity_remaining.get());
            checksum += bench::digest(message->trade_type.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->trade_price.integer());
            checksum += bench::digest(message->opposite_tradeable_instrument_id.get());
            checksum += bench::digest(message->opposite_side.get());
            checksum += bench::digest(message->opposite_order_id.get());
            checksum += bench::digest(message->combination_trade_id.get());
        } else if (iterator.message_type == protocol::ImpliedOrderAddedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ImpliedOrderAddedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_book_priority.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::ImpliedOrderReplacedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ImpliedOrderReplacedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_id.get());
            checksum += bench::digest(message->order_book_priority.get());
            checksum += bench::digest(message->quantity.get());
            checksum += bench::digest(message->price.integer());
        } else if (iterator.message_type == protocol::ImpliedOrderDeletedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::ImpliedOrderDeletedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->side.get());
            checksum += bench::digest(message->order_id.get());
        } else if (iterator.message_type == protocol::TradeExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->trade_type.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->trade_price.integer());
            checksum += bench::digest(message->combination_trade_id.get());
            checksum += bench::digest(message->participant_id_buyer.get());
            checksum += bench::digest(message->participant_id_seller.get());
        } else if (iterator.message_type == protocol::CombinationTradeExecutedMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::CombinationTradeExecutedMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->trade_type.get());
            checksum += bench::digest(message->trade_id.get());
            checksum += bench::digest(message->executed_quantity.get());
            checksum += bench::digest(message->trade_price.integer());
            checksum += bench::digest(message->buyer_tradeable_instrument_id.get());
            checksum += bench::digest(message->buyer_side.get());
            checksum += bench::digest(message->buyer_order_id.get());
            checksum += bench::digest(message->buyer_combination_trade_id.get());
            checksum += bench::digest(message->buyer_participant_id.get());
            checksum += bench::digest(message->seller_tradeable_instrument_id.get());
            checksum += bench::digest(message->seller_side.get());
            checksum += bench::digest(message->seller_order_id.get());
            checksum += bench::digest(message->seller_combination_trade_id.get());
            checksum += bench::digest(message->seller_participant_id.get());
        } else if (iterator.message_type == protocol::TradeCancellationMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TradeCancellationMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->trade_id.get());
        } else if (iterator.message_type == protocol::EquilibriumPriceMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::EquilibriumPriceMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->equilibrium_price.integer());
            checksum += bench::digest(message->matched_quantity.get());
            checksum += bench::digest(message->bid_quantity.get());
            checksum += bench::digest(message->ask_quantity.get());
        } else if (iterator.message_type == protocol::OpenHighLowLastTradeAdjustmentMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::OpenHighLowLastTradeAdjustmentMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->opening_trade.integer());
            checksum += bench::digest(message->highest_trade.integer());
            checksum += bench::digest(message->lowest_trade.integer());
            checksum += bench::digest(message->last_trade.integer());
            checksum += bench::digest(message->last_volume.get());
            checksum += bench::digest(message->total_traded_volume.get());
        } else if (iterator.message_type == protocol::MarketSettlementMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::MarketSettlementMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->opening_trade.integer());
            checksum += bench::digest(message->highest_trade.integer());
            checksum += bench::digest(message->lowest_trade.integer());
            checksum += bench::digest(message->last_trade.integer());
            checksum += bench::digest(message->last_volume.get());
            checksum += bench::digest(message->total_traded_volume.get());
        } else if (iterator.message_type == protocol::TextMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::TextMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->source_id.get());
            checksum += bench::digest(message->text.get());
        } else if (iterator.message_type == protocol::RequestForQuoteMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::RequestForQuoteMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->rfq_side.get());
            checksum += bench::digest(message->quantity.get());
        } else if (iterator.message_type == protocol::AnomalousOrderThresholdPublishMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::AnomalousOrderThresholdPublishMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->aot_price.integer());
            checksum += bench::digest(message->aot_upper_price.integer());
            checksum += bench::digest(message->aot_lower_price.integer());
            checksum += bench::digest(message->etr_price.integer());
            checksum += bench::digest(message->etr_upper_price.integer());
            checksum += bench::digest(message->etr_lower_price.integer());
        } else if (iterator.message_type == protocol::VolumeAndOpenInterestMessage::message_type) {
            [[maybe_unused]] const auto* message = protocol::VolumeAndOpenInterestMessage::parse(iterator.message);
            checksum += bench::digest(message->nanoseconds.get());
            checksum += bench::digest(message->trade_date.get());
            checksum += bench::digest(message->tradeable_instrument_id.get());
            checksum += bench::digest(message->cumulative_volume.get());
            checksum += bench::digest(message->open_interest.get());
            checksum += bench::digest(message->voi_trade_date.get());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Asx.AsxDerivatives.Ntp.Itch.v1.05", "modern", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
