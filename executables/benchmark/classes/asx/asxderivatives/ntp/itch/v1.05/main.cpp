// Asx.AsxDerivatives.Ntp.Itch.v1.05 benchmark, through the Classes Packet: every value it reads from every message of the simulated
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
#include "cpp/binary/classes/asx/asxderivatives/ntp/itch/v1.05/definitions.hpp"

namespace protocol = ::asx::asxderivatives::ntp::itch::v1_05;

namespace {

// The values the Classes Packet decodes from one datagram, folded into a checksum. A datagram it cannot
// decode is a value the model never reads, so the benchmark refuses to time it.
std::uint64_t read(const packet::Frame& frame) {
    std::uint64_t checksum = 0;
    protocol::Packet packet;

    try {
        packet.decode(frame.payload, frame.payload_len);
    } catch (const protocol::DecodeError& error) {
        throw;
        return checksum;
    }

    checksum += bench::digest(packet.packet_header().session());
    checksum += bench::digest(packet.packet_header().sequence_number());
    checksum += bench::digest(packet.packet_header().message_count());

    std::size_t index = 0;

    for (const auto& each : packet.frames()) {
        checksum += index++;
        checksum += bench::digest(each.message_header().message_length());
        checksum += bench::digest(each.message_header().message_type());

        if (const auto* message = dynamic_cast<const protocol::SecondsMessage*>(each.message())) {
            checksum += bench::digest((*message).second());
        } else if (const auto* message = dynamic_cast<const protocol::EndOfBusinessTradeDateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).event_code());
        } else if (const auto* message = dynamic_cast<const protocol::FutureSymbolDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).symbol_name());
            checksum += bench::digest((*message).long_name());
            checksum += bench::digest((*message).isin());
            checksum += bench::digest((*message).exchange());
            checksum += bench::digest((*message).instrument());
            checksum += bench::digest((*message).cfi_code());
            checksum += bench::digest((*message).expiry_year());
            checksum += bench::digest((*message).expiry_month());
            checksum += bench::digest((*message).price_display_decimals());
            checksum += bench::digest((*message).price_fractional_denominator());
            checksum += bench::digest((*message).price_minimum_tick());
            checksum += bench::digest((*message).last_trading_date());
            checksum += bench::digest((*message).prior_day_settlement().mantissa());
            checksum += bench::digest((*message).currency());
            checksum += bench::digest((*message).lot_size_or_face_value());
            checksum += bench::digest((*message).maturity_value());
            checksum += bench::digest((*message).coupon_rate());
            checksum += bench::digest((*message).payments_per_year());
            checksum += bench::digest((*message).block_lot_size());
            checksum += bench::digest((*message).expiry_date());
        } else if (const auto* message = dynamic_cast<const protocol::OptionsSymbolDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).symbol_name());
            checksum += bench::digest((*message).long_name());
            checksum += bench::digest((*message).isin());
            checksum += bench::digest((*message).exchange());
            checksum += bench::digest((*message).instrument());
            checksum += bench::digest((*message).cfi_code());
            checksum += bench::digest((*message).expiry_year());
            checksum += bench::digest((*message).expiry_month());
            checksum += bench::digest((*message).option_type());
            checksum += bench::digest((*message).strike().mantissa());
            checksum += bench::digest((*message).underlying_tradeable_instrument_id());
            checksum += bench::digest((*message).price_display_decimals());
            checksum += bench::digest((*message).price_fractional_denominator());
            checksum += bench::digest((*message).price_minimum_tick());
            checksum += bench::digest((*message).strike_price_decimal_position());
            checksum += bench::digest((*message).strike_price_fractional_denominator());
            checksum += bench::digest((*message).strike_price_minimum_tick());
            checksum += bench::digest((*message).last_trading_date());
            checksum += bench::digest((*message).prior_day_settlement().mantissa());
            checksum += bench::digest((*message).volatility());
            checksum += bench::digest((*message).currency());
            checksum += bench::digest((*message).lot_size_or_face_value());
            checksum += bench::digest((*message).maturity_value());
            checksum += bench::digest((*message).coupon_rate());
            checksum += bench::digest((*message).payments_per_year());
            checksum += bench::digest((*message).block_lot_size());
            checksum += bench::digest((*message).expiry_date());
            checksum += bench::digest((*message).basis_of_quotation());
        } else if (const auto* message = dynamic_cast<const protocol::CombinationSymbolDirectoryMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).symbol_name());
            checksum += bench::digest((*message).long_name());
            checksum += bench::digest((*message).cfi_code());
            checksum += bench::digest((*message).price_method());
            checksum += bench::digest((*message).price_display_decimals());
            checksum += bench::digest((*message).price_fractional_denominator());
            checksum += bench::digest((*message).price_minimum_tick());
            checksum += bench::digest((*message).legs());
        } else if (const auto* message = dynamic_cast<const protocol::BundlesSymbolDirectory*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).symbol_name());
            checksum += bench::digest((*message).long_name());
            checksum += bench::digest((*message).cfi_code());
            checksum += bench::digest((*message).price_method());
            checksum += bench::digest((*message).price_display_decimals());
            checksum += bench::digest((*message).price_fractional_denominator());
            checksum += bench::digest((*message).price_minimum_tick());
            checksum += bench::digest((*message).legs());
        } else if (const auto* message = dynamic_cast<const protocol::OrderBookStateMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).session_state());
        } else if (const auto* message = dynamic_cast<const protocol::AddOrderMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_book_priority());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::OrderVolumeCancelledMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity());
        } else if (const auto* message = dynamic_cast<const protocol::OrderDeletedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::OrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity_remaining());
            checksum += bench::digest((*message).trade_type());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).trade_price().mantissa());
            checksum += bench::digest((*message).combination_trade_id());
            checksum += bench::digest((*message).counter_party_id());
        } else if (const auto* message = dynamic_cast<const protocol::AuctionOrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity_remaining());
            checksum += bench::digest((*message).trade_type());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).trade_price().mantissa());
            checksum += bench::digest((*message).opposite_order_id());
        } else if (const auto* message = dynamic_cast<const protocol::CombinationOrderExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).quantity_remaining());
            checksum += bench::digest((*message).trade_type());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).trade_price().mantissa());
            checksum += bench::digest((*message).opposite_tradeable_instrument_id());
            checksum += bench::digest((*message).opposite_side());
            checksum += bench::digest((*message).opposite_order_id());
            checksum += bench::digest((*message).combination_trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::ImpliedOrderAddedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_book_priority());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::ImpliedOrderReplacedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_id());
            checksum += bench::digest((*message).order_book_priority());
            checksum += bench::digest((*message).quantity());
            checksum += bench::digest((*message).price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::ImpliedOrderDeletedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).side());
            checksum += bench::digest((*message).order_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).trade_type());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).trade_price().mantissa());
            checksum += bench::digest((*message).combination_trade_id());
            checksum += bench::digest((*message).participant_id_buyer());
            checksum += bench::digest((*message).participant_id_seller());
        } else if (const auto* message = dynamic_cast<const protocol::CombinationTradeExecutedMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).trade_type());
            checksum += bench::digest((*message).trade_id());
            checksum += bench::digest((*message).executed_quantity());
            checksum += bench::digest((*message).trade_price().mantissa());
            checksum += bench::digest((*message).buyer_tradeable_instrument_id());
            checksum += bench::digest((*message).buyer_side());
            checksum += bench::digest((*message).buyer_order_id());
            checksum += bench::digest((*message).buyer_combination_trade_id());
            checksum += bench::digest((*message).buyer_participant_id());
            checksum += bench::digest((*message).seller_tradeable_instrument_id());
            checksum += bench::digest((*message).seller_side());
            checksum += bench::digest((*message).seller_order_id());
            checksum += bench::digest((*message).seller_combination_trade_id());
            checksum += bench::digest((*message).seller_participant_id());
        } else if (const auto* message = dynamic_cast<const protocol::TradeCancellationMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).trade_id());
        } else if (const auto* message = dynamic_cast<const protocol::EquilibriumPriceMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).equilibrium_price().mantissa());
            checksum += bench::digest((*message).matched_quantity());
            checksum += bench::digest((*message).bid_quantity());
            checksum += bench::digest((*message).ask_quantity());
        } else if (const auto* message = dynamic_cast<const protocol::OpenHighLowLastTradeAdjustmentMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).opening_trade().mantissa());
            checksum += bench::digest((*message).highest_trade().mantissa());
            checksum += bench::digest((*message).lowest_trade().mantissa());
            checksum += bench::digest((*message).last_trade().mantissa());
            checksum += bench::digest((*message).last_volume());
            checksum += bench::digest((*message).total_traded_volume());
        } else if (const auto* message = dynamic_cast<const protocol::MarketSettlementMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).opening_trade().mantissa());
            checksum += bench::digest((*message).highest_trade().mantissa());
            checksum += bench::digest((*message).lowest_trade().mantissa());
            checksum += bench::digest((*message).last_trade().mantissa());
            checksum += bench::digest((*message).last_volume());
            checksum += bench::digest((*message).total_traded_volume());
        } else if (const auto* message = dynamic_cast<const protocol::TextMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).source_id());
            checksum += bench::digest((*message).text());
        } else if (const auto* message = dynamic_cast<const protocol::RequestForQuoteMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).rfq_side());
            checksum += bench::digest((*message).quantity());
        } else if (const auto* message = dynamic_cast<const protocol::AnomalousOrderThresholdPublishMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).aot_price().mantissa());
            checksum += bench::digest((*message).aot_upper_price().mantissa());
            checksum += bench::digest((*message).aot_lower_price().mantissa());
            checksum += bench::digest((*message).etr_price().mantissa());
            checksum += bench::digest((*message).etr_upper_price().mantissa());
            checksum += bench::digest((*message).etr_lower_price().mantissa());
        } else if (const auto* message = dynamic_cast<const protocol::VolumeAndOpenInterestMessage*>(each.message())) {
            checksum += bench::digest((*message).nanoseconds());
            checksum += bench::digest((*message).trade_date());
            checksum += bench::digest((*message).tradeable_instrument_id());
            checksum += bench::digest((*message).cumulative_volume());
            checksum += bench::digest((*message).open_interest());
            checksum += bench::digest((*message).voi_trade_date());
        }
    }

    return checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Asx.AsxDerivatives.Ntp.Itch.v1.05", "classes", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
