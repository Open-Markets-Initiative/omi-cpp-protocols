// Asx.AsxDerivatives.Ntp.Itch.v1.05 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
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
#include "cpp/binary/advanced/asx/asxderivatives/ntp/itch/v1.05/messages/session.hpp"

namespace protocol = ::asx::asxderivatives::ntp::itch::v1_05;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        checksum += bench::digest(header.session.get().value());
        checksum += bench::digest(header.sequence_number.get().value());
        checksum += bench::digest(header.message_count.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::seconds_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.second.get().value());
    }

    void on_message(const protocol::end_of_business_trade_date_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.event_code.get().value());
    }

    void on_message(const protocol::future_symbol_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.symbol_name.get().value());
        checksum += bench::digest(message.fields.long_name.get().value());
        checksum += bench::digest(message.fields.isin.get().value());
        checksum += bench::digest(message.fields.exchange.get().value());
        checksum += bench::digest(message.fields.instrument.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += bench::digest(message.fields.expiry_year.get().value());
        checksum += bench::digest(message.fields.expiry_month.get().value());
        checksum += bench::digest(message.fields.price_display_decimals.get().value());
        checksum += bench::digest(message.fields.price_fractional_denominator.get().value());
        checksum += bench::digest(message.fields.price_minimum_tick.get().value());
        checksum += bench::digest(message.fields.last_trading_date.get().value());
        checksum += bench::digest(message.fields.prior_day_settlement.get().value());
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += bench::digest(message.fields.lot_size_or_face_value.get().value());
        checksum += bench::digest(message.fields.maturity_value.get().value());
        checksum += bench::digest(message.fields.coupon_rate.get().value());
        checksum += bench::digest(message.fields.payments_per_year.get().value());
        checksum += bench::digest(message.fields.block_lot_size.get().value());
        checksum += bench::digest(message.fields.expiry_date.get().value());
    }

    void on_message(const protocol::options_symbol_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.symbol_name.get().value());
        checksum += bench::digest(message.fields.long_name.get().value());
        checksum += bench::digest(message.fields.isin.get().value());
        checksum += bench::digest(message.fields.exchange.get().value());
        checksum += bench::digest(message.fields.instrument.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += bench::digest(message.fields.expiry_year.get().value());
        checksum += bench::digest(message.fields.expiry_month.get().value());
        checksum += bench::digest(message.fields.option_type.get().value());
        checksum += bench::digest(message.fields.strike.get().value());
        checksum += bench::digest(message.fields.underlying_tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.price_display_decimals.get().value());
        checksum += bench::digest(message.fields.price_fractional_denominator.get().value());
        checksum += bench::digest(message.fields.price_minimum_tick.get().value());
        checksum += bench::digest(message.fields.strike_price_decimal_position.get().value());
        checksum += bench::digest(message.fields.strike_price_fractional_denominator.get().value());
        checksum += bench::digest(message.fields.strike_price_minimum_tick.get().value());
        checksum += bench::digest(message.fields.last_trading_date.get().value());
        checksum += bench::digest(message.fields.prior_day_settlement.get().value());
        checksum += bench::digest(message.fields.volatility.get().value());
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += bench::digest(message.fields.lot_size_or_face_value.get().value());
        checksum += bench::digest(message.fields.maturity_value.get().value());
        checksum += bench::digest(message.fields.coupon_rate.get().value());
        checksum += bench::digest(message.fields.payments_per_year.get().value());
        checksum += bench::digest(message.fields.block_lot_size.get().value());
        checksum += bench::digest(message.fields.expiry_date.get().value());
        checksum += bench::digest(message.fields.basis_of_quotation.get().value());
    }

    void on_message(const protocol::combination_symbol_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.symbol_name.get().value());
        checksum += bench::digest(message.fields.long_name.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += bench::digest(message.fields.price_method.get().value());
        checksum += bench::digest(message.fields.price_display_decimals.get().value());
        checksum += bench::digest(message.fields.price_fractional_denominator.get().value());
        checksum += bench::digest(message.fields.price_minimum_tick.get().value());
        checksum += bench::digest(message.fields.legs.get().value());
    }

    void on_message(const protocol::bundles_symbol_directory& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.symbol_name.get().value());
        checksum += bench::digest(message.fields.long_name.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += bench::digest(message.fields.price_method.get().value());
        checksum += bench::digest(message.fields.price_display_decimals.get().value());
        checksum += bench::digest(message.fields.price_fractional_denominator.get().value());
        checksum += bench::digest(message.fields.price_minimum_tick.get().value());
        checksum += bench::digest(message.fields.legs.get().value());
    }

    void on_message(const protocol::order_book_state_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.session_state.get().value());
    }

    void on_message(const protocol::add_order_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.order_book_priority.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::order_volume_cancelled_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
    }

    void on_message(const protocol::order_deleted_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
    }

    void on_message(const protocol::order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.quantity_remaining.get().value());
        checksum += bench::digest(message.fields.trade_type.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.combination_trade_id.get().value());
        checksum += bench::digest(message.fields.counter_party_id.get().value());
    }

    void on_message(const protocol::auction_order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.quantity_remaining.get().value());
        checksum += bench::digest(message.fields.trade_type.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.opposite_order_id.get().value());
    }

    void on_message(const protocol::combination_order_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.quantity_remaining.get().value());
        checksum += bench::digest(message.fields.trade_type.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.opposite_tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.opposite_side.get().value());
        checksum += bench::digest(message.fields.opposite_order_id.get().value());
        checksum += bench::digest(message.fields.combination_trade_id.get().value());
    }

    void on_message(const protocol::implied_order_added_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.order_book_priority.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::implied_order_replaced_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
        checksum += bench::digest(message.fields.order_book_priority.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
        checksum += bench::digest(message.fields.price.get().value());
    }

    void on_message(const protocol::implied_order_deleted_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.side.get().value());
        checksum += bench::digest(message.fields.order_id.get().value());
    }

    void on_message(const protocol::trade_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.trade_type.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.combination_trade_id.get().value());
        checksum += bench::digest(message.fields.participant_id_buyer.get().value());
        checksum += bench::digest(message.fields.participant_id_seller.get().value());
    }

    void on_message(const protocol::combination_trade_executed_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.trade_type.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.executed_quantity.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.buyer_tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.buyer_side.get().value());
        checksum += bench::digest(message.fields.buyer_order_id.get().value());
        checksum += bench::digest(message.fields.buyer_combination_trade_id.get().value());
        checksum += bench::digest(message.fields.buyer_participant_id.get().value());
        checksum += bench::digest(message.fields.seller_tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.seller_side.get().value());
        checksum += bench::digest(message.fields.seller_order_id.get().value());
        checksum += bench::digest(message.fields.seller_combination_trade_id.get().value());
        checksum += bench::digest(message.fields.seller_participant_id.get().value());
    }

    void on_message(const protocol::trade_cancellation_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
    }

    void on_message(const protocol::equilibrium_price_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.equilibrium_price.get().value());
        checksum += bench::digest(message.fields.matched_quantity.get().value());
        checksum += bench::digest(message.fields.bid_quantity.get().value());
        checksum += bench::digest(message.fields.ask_quantity.get().value());
    }

    void on_message(const protocol::open_high_low_last_trade_adjustment_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.opening_trade.get().value());
        checksum += bench::digest(message.fields.highest_trade.get().value());
        checksum += bench::digest(message.fields.lowest_trade.get().value());
        checksum += bench::digest(message.fields.last_trade.get().value());
        checksum += bench::digest(message.fields.last_volume.get().value());
        checksum += bench::digest(message.fields.total_traded_volume.get().value());
    }

    void on_message(const protocol::market_settlement_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.opening_trade.get().value());
        checksum += bench::digest(message.fields.highest_trade.get().value());
        checksum += bench::digest(message.fields.lowest_trade.get().value());
        checksum += bench::digest(message.fields.last_trade.get().value());
        checksum += bench::digest(message.fields.last_volume.get().value());
        checksum += bench::digest(message.fields.total_traded_volume.get().value());
    }

    void on_message(const protocol::text_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.source_id.get().value());
        checksum += bench::digest(message.fields.text.get().value());
    }

    void on_message(const protocol::request_for_quote_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.rfq_side.get().value());
        checksum += bench::digest(message.fields.quantity.get().value());
    }

    void on_message(const protocol::anomalous_order_threshold_publish_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.aot_price.get().value());
        checksum += bench::digest(message.fields.aot_upper_price.get().value());
        checksum += bench::digest(message.fields.aot_lower_price.get().value());
        checksum += bench::digest(message.fields.etr_price.get().value());
        checksum += bench::digest(message.fields.etr_upper_price.get().value());
        checksum += bench::digest(message.fields.etr_lower_price.get().value());
    }

    void on_message(const protocol::volume_and_open_interest_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.tradeable_instrument_id.get().value());
        checksum += bench::digest(message.fields.cumulative_volume.get().value());
        checksum += bench::digest(message.fields.open_interest.get().value());
        checksum += bench::digest(message.fields.voi_trade_date.get().value());
    }
};

// The values Advanced reads from one datagram, folded into a checksum
std::uint64_t read(const packet::Frame& frame) {
    Reader reader;
    protocol::process_segment(reader, frame.payload, frame.payload_len, 0, frame);
    return reader.checksum;
}

}

int main(int argc, char** argv) {
    // read named through a call, as POSIX declares a read of its own
    return bench::run("Asx.AsxDerivatives.Ntp.Itch.v1.05", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
