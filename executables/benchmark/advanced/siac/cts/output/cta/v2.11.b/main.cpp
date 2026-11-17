// Siac.Cts.Output.Cta.v2.11.b: main.cpp
// Siac.Cts.Output.Cta.v2.11.b benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/siac/cts/output/cta/v2.11.b.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/siac/cts/output/cta/v2.11.b/messages/session.hpp"

namespace protocol = ::siac::cts::output::cta::v2_11_b;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::block_header& header, const packet::Frame&) {
        checksum += bench::digest(header.version.get().value());
        checksum += bench::digest(header.block_size.get().value());
        checksum += bench::digest(header.data_feed_indicator.get().value());
        checksum += bench::digest(header.retransmission_indicator.get().value());
        checksum += bench::digest(header.block_sequence_number.get().value());
        checksum += bench::digest(header.messages_in_block.get().value());
        checksum += bench::digest(header.sip_block_timestamp.seconds.get().value());
        checksum += bench::digest(header.sip_block_timestamp.nanoseconds.get().value());
        checksum += bench::digest(header.block_checksum.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::block_header&) {
        ++index;
    }

    void on_message(const protocol::start_of_end_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.administrative_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::end_of_end_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.administrative_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::start_of_start_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.administrative_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::end_of_start_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.administrative_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::symbol_reference_data_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.administrative_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.prior_security_symbol.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_previous_closing_price.get().value());
        checksum += bench::digest(message.fields.consolidated_closing_price.get().value());
        checksum += bench::digest(message.fields.round_lot_size.get().value());
        checksum += bench::digest(message.fields.minimum_price_increment_indicator.get().value());
        checksum += bench::digest(message.fields.luld_tier.get().value());
        checksum += bench::digest(message.fields.luld_leverage_ratio.get().value());
        checksum += bench::digest(message.fields.test.get().value());
        checksum += bench::digest(message.fields.ipo.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.halt_reason.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
    }

    void on_message(const protocol::start_of_day_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::reset_block_sequence_number_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::disaster_recovery_data_center_activation_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::line_integrity_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::end_of_day_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.control_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
    }

    void on_message(const protocol::index_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.indices_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.index_symbol.get().value());
        checksum += bench::digest(message.fields.index_value.get().value());
    }

    void on_message(const protocol::bid_and_offer_index_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.indices_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.index_symbol.get().value());
        checksum += bench::digest(message.fields.bid_index_value.get().value());
        checksum += bench::digest(message.fields.offer_index_value.get().value());
    }

    void on_message(const protocol::market_wide_circuit_breaker_decline_level_status_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.mwcb_level_1.get().value());
        checksum += bench::digest(message.fields.mwcb_level_2.get().value());
        checksum += bench::digest(message.fields.mwcb_level_3.get().value());
    }

    void on_message(const protocol::market_wide_circuit_breaker_status_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.market_wide_circuit_breaker_level_indicator.get().value());
    }

    void on_message(const protocol::approximate_adjusted_volume_market_center_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.number_of_participants.get().value());
    }

    void on_message(const protocol::fractional_approximate_adjusted_volume_market_center_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.number_of_participants.get().value());
    }

    void on_message(const protocol::approximate_trades_and_total_dollar_value_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.total_trades.get().value());
        checksum += bench::digest(message.fields.dollar_value.get().value());
    }

    void on_message(const protocol::crossing_session_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.market_status_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.crossing_session_i_total_trades_volume.get().value());
        checksum += bench::digest(message.fields.crossing_session_ii_dollar_value.get().value());
        checksum += bench::digest(message.fields.crossing_session_ii_total_trades_volume.get().value());
    }

    void on_message(const protocol::prior_day_trade_correction_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.prior_day_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition.get().value());
        checksum += bench::digest(message.fields.corrected_trade_price.get().value());
        checksum += bench::digest(message.fields.corrected_trade_volume.get().value());
        checksum += bench::digest(message.fields.corrected_sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.corrected_stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.corrected_trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.corrected_short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.corrected_prior_day_trade_date_and_time.seconds.get().value());
        checksum += bench::digest(message.fields.corrected_prior_day_trade_date_and_time.nanoseconds.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.original_sale_condition.get().value());
        checksum += bench::digest(message.fields.original_trade_price.get().value());
        checksum += bench::digest(message.fields.original_trade_volume.get().value());
        checksum += bench::digest(message.fields.original_sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.original_stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.original_trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.original_short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.original_prior_day_trade_date_and_time.seconds.get().value());
        checksum += bench::digest(message.fields.original_prior_day_trade_date_and_time.nanoseconds.get().value());
    }

    void on_message(const protocol::prior_day_trade_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.prior_day_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_2.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_3.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_4.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.trade_volume.get().value());
        checksum += bench::digest(message.fields.sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.seconds.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.nanoseconds.get().value());
    }

    void on_message(const protocol::prior_day_trade_cancel_error_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.prior_day_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_2.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_3.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_4.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.trade_volume.get().value());
        checksum += bench::digest(message.fields.sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.seconds.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.nanoseconds.get().value());
        checksum += bench::digest(message.fields.cancel_error_action.get().value());
    }

    void on_message(const protocol::fractional_prior_day_trade_correction_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.prior_day_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_2.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_3.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_4.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.fractional_trade_volume.get().value());
        checksum += bench::digest(message.fields.sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.seconds.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.nanoseconds.get().value());
    }

    void on_message(const protocol::fractional_prior_day_trade_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.prior_day_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_2.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_3.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_4.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.fractional_trade_volume.get().value());
        checksum += bench::digest(message.fields.sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.seconds.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.nanoseconds.get().value());
    }

    void on_message(const protocol::fractional_prior_day_trade_cancel_error_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.prior_day_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_2.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_3.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_4.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.fractional_trade_volume.get().value());
        checksum += bench::digest(message.fields.sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.seconds.get().value());
        checksum += bench::digest(message.fields.prior_day_trade_date_and_time.nanoseconds.get().value());
        checksum += bench::digest(message.fields.cancel_error_action.get().value());
    }

    void on_message(const protocol::consolidated_start_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.summary_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.summary_participant_id.get().value());
        checksum += bench::digest(message.fields.previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.previous_close_price.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.number_of_participants.get().value());
    }

    void on_message(const protocol::participant_start_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.summary_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.summary_participant_id.get().value());
        checksum += bench::digest(message.fields.previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.previous_close_price.get().value());
    }

    void on_message(const protocol::consolidated_end_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.summary_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.last_participant_id.get().value());
        checksum += bench::digest(message.fields.previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.last_price.get().value());
        checksum += bench::digest(message.fields.high_price.get().value());
        checksum += bench::digest(message.fields.low_price.get().value());
        checksum += bench::digest(message.fields.total_volume.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.number_of_participants.get().value());
    }

    void on_message(const protocol::fractional_consolidated_end_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.summary_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.last_participant_id.get().value());
        checksum += bench::digest(message.fields.previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.last_price.get().value());
        checksum += bench::digest(message.fields.high_price.get().value());
        checksum += bench::digest(message.fields.low_price.get().value());
        checksum += bench::digest(message.fields.fractional_total_volume.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.number_of_participants.get().value());
    }

    void on_message(const protocol::participant_end_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.summary_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.summary_participant_id.get().value());
        checksum += bench::digest(message.fields.previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.last_price.get().value());
        checksum += bench::digest(message.fields.high_price.get().value());
        checksum += bench::digest(message.fields.low_price.get().value());
        checksum += bench::digest(message.fields.open_price.get().value());
        checksum += bench::digest(message.fields.total_volume.get().value());
        checksum += bench::digest(message.fields.tick.get().value());
    }

    void on_message(const protocol::fractional_participant_end_of_day_summary_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.summary_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.summary_participant_id.get().value());
        checksum += bench::digest(message.fields.previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.last_price.get().value());
        checksum += bench::digest(message.fields.high_price.get().value());
        checksum += bench::digest(message.fields.low_price.get().value());
        checksum += bench::digest(message.fields.open_price.get().value());
        checksum += bench::digest(message.fields.fractional_total_volume.get().value());
        checksum += bench::digest(message.fields.tick.get().value());
    }

    void on_message(const protocol::auction_status_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.auction_collar_reference_price.get().value());
        checksum += bench::digest(message.fields.auction_collar_upper_threshold_price.get().value());
        checksum += bench::digest(message.fields.auction_collar_lower_threshold_price.get().value());
        checksum += bench::digest(message.fields.number_of_extensions.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
    }

    void on_message(const protocol::trade_correction_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition.get().value());
        checksum += bench::digest(message.fields.corrected_trade_price.get().value());
        checksum += bench::digest(message.fields.corrected_trade_volume.get().value());
        checksum += bench::digest(message.fields.corrected_sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.corrected_stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.corrected_trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.corrected_short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.original_participant_reference_number.get().value());
        checksum += bench::digest(message.fields.original_sale_condition.get().value());
        checksum += bench::digest(message.fields.original_trade_price.get().value());
        checksum += bench::digest(message.fields.original_trade_volume.get().value());
        checksum += bench::digest(message.fields.original_sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.original_stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.original_trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.original_short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.consolidated_previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.consolidated_last_participant_id.get().value());
        checksum += bench::digest(message.fields.consolidated_last_price.get().value());
        checksum += bench::digest(message.fields.consolidated_high_price.get().value());
        checksum += bench::digest(message.fields.consolidated_low_price.get().value());
        checksum += bench::digest(message.fields.consolidated_total_volume.get().value());
        checksum += bench::digest(message.fields.consolidated_tick.get().value());
        checksum += bench::digest(message.fields.participant_previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.participant_last_price.get().value());
        checksum += bench::digest(message.fields.participant_high_price.get().value());
        checksum += bench::digest(message.fields.participant_low_price.get().value());
        checksum += bench::digest(message.fields.participant_open_price.get().value());
        checksum += bench::digest(message.fields.participant_total_volume.get().value());
        checksum += bench::digest(message.fields.participant_tick.get().value());
    }

    void on_message(const protocol::long_trade_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_2.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_3.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_4.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.trade_volume.get().value());
        checksum += bench::digest(message.fields.sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.held_trade_indicator.get().value());
        checksum += bench::digest(message.fields.consolidated_high_low_last_indicator.get().value());
        checksum += bench::digest(message.fields.participant_open_high_low_last_indicator.get().value());
    }

    void on_message(const protocol::short_trade_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol_5.get().value());
        checksum += bench::digest(message.fields.sale_condition_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_category.get().value());
        checksum += bench::digest(message.fields.trade_price_2.get().value());
        checksum += bench::digest(message.fields.trade_volume_2.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.consolidated_high_low_last_indicator.get().value());
        checksum += bench::digest(message.fields.participant_open_high_low_last_indicator.get().value());
    }

    void on_message(const protocol::trade_cancel_error_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_2.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_3.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_4.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.trade_volume.get().value());
        checksum += bench::digest(message.fields.sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.original_participant_reference_number.get().value());
        checksum += bench::digest(message.fields.cancel_error_action.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.consolidated_previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.consolidated_last_participant_id.get().value());
        checksum += bench::digest(message.fields.consolidated_last_price.get().value());
        checksum += bench::digest(message.fields.consolidated_high_price.get().value());
        checksum += bench::digest(message.fields.consolidated_low_price.get().value());
        checksum += bench::digest(message.fields.consolidated_total_volume.get().value());
        checksum += bench::digest(message.fields.consolidated_tick.get().value());
        checksum += bench::digest(message.fields.participant_previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.participant_last_price.get().value());
        checksum += bench::digest(message.fields.participant_high_price.get().value());
        checksum += bench::digest(message.fields.participant_low_price.get().value());
        checksum += bench::digest(message.fields.participant_open_price.get().value());
        checksum += bench::digest(message.fields.participant_total_volume.get().value());
        checksum += bench::digest(message.fields.participant_tick.get().value());
    }

    void on_message(const protocol::fractional_trade_correction_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition.get().value());
        checksum += bench::digest(message.fields.corrected_trade_price.get().value());
        checksum += bench::digest(message.fields.corrected_fractional_trade_volume.get().value());
        checksum += bench::digest(message.fields.corrected_sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.corrected_stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.corrected_trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.corrected_short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.original_participant_reference_number.get().value());
        checksum += bench::digest(message.fields.original_sale_condition.get().value());
        checksum += bench::digest(message.fields.original_trade_price.get().value());
        checksum += bench::digest(message.fields.original_fractional_trade_volume.get().value());
        checksum += bench::digest(message.fields.original_sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.original_stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.original_trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.original_short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.consolidated_previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.consolidated_last_participant_id.get().value());
        checksum += bench::digest(message.fields.consolidated_last_price.get().value());
        checksum += bench::digest(message.fields.consolidated_high_price.get().value());
        checksum += bench::digest(message.fields.consolidated_low_price.get().value());
        checksum += bench::digest(message.fields.consolidated_fractional_total_volume.get().value());
        checksum += bench::digest(message.fields.consolidated_tick.get().value());
        checksum += bench::digest(message.fields.participant_previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.participant_last_price.get().value());
        checksum += bench::digest(message.fields.participant_high_price.get().value());
        checksum += bench::digest(message.fields.participant_low_price.get().value());
        checksum += bench::digest(message.fields.participant_open_price.get().value());
        checksum += bench::digest(message.fields.participant_fractional_total_volume.get().value());
        checksum += bench::digest(message.fields.participant_tick.get().value());
    }

    void on_message(const protocol::fractional_long_trade_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_2.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_3.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_4.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.fractional_trade_volume.get().value());
        checksum += bench::digest(message.fields.sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.held_trade_indicator.get().value());
        checksum += bench::digest(message.fields.consolidated_high_low_last_indicator.get().value());
        checksum += bench::digest(message.fields.participant_open_high_low_last_indicator.get().value());
    }

    void on_message(const protocol::trading_status_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.last_price.get().value());
        checksum += bench::digest(message.fields.high_indication_price_upper_limit_price_band.get().value());
        checksum += bench::digest(message.fields.low_indication_price_lower_limit_price_band.get().value());
        checksum += bench::digest(message.fields.buy_volume.get().value());
        checksum += bench::digest(message.fields.sell_volume.get().value());
        checksum += bench::digest(message.fields.security_status.get().value());
        checksum += bench::digest(message.fields.halt_reason.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.limit_up_limit_down_luld_indicator.get().value());
    }

    void on_message(const protocol::fractional_short_trade_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol_5.get().value());
        checksum += bench::digest(message.fields.sale_condition_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_category.get().value());
        checksum += bench::digest(message.fields.trade_price_2.get().value());
        checksum += bench::digest(message.fields.fractional_trade_volume_4.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.consolidated_high_low_last_indicator.get().value());
        checksum += bench::digest(message.fields.participant_open_high_low_last_indicator.get().value());
    }

    void on_message(const protocol::fractional_trade_cancel_error_message& message, std::uint64_t, const protocol::block_header&) {
        checksum += index++;
        checksum += bench::digest(message.trade_message_type.get().value());
        checksum += bench::digest(message.fields.participant_id.get().value());
        checksum += bench::digest(message.fields.timestamp_1.seconds.get().value());
        checksum += bench::digest(message.fields.timestamp_1.nanoseconds.get().value());
        checksum += bench::digest(message.fields.message_id.get().value());
        checksum += bench::digest(message.fields.transaction_id.get().value());
        checksum += bench::digest(message.fields.participant_reference_number.get().value());
        checksum += bench::digest(message.fields.security_symbol.get().value());
        checksum += bench::digest(message.fields.instrument_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_1.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_2.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_3.get().value());
        checksum += bench::digest(message.fields.sale_condition_4.category_4.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.fractional_trade_volume.get().value());
        checksum += bench::digest(message.fields.sellers_sale_days.get().value());
        checksum += bench::digest(message.fields.stop_stock_indicator.get().value());
        checksum += bench::digest(message.fields.trade_through_exempt_indicator.get().value());
        checksum += bench::digest(message.fields.trade_reporting_facility_id.get().value());
        checksum += bench::digest(message.fields.original_participant_reference_number.get().value());
        checksum += bench::digest(message.fields.cancel_error_action.get().value());
        checksum += bench::digest(message.fields.short_sale_restriction_indicator.get().value());
        checksum += bench::digest(message.fields.primary_listing_market_participant_id.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.consolidated_previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.consolidated_last_participant_id.get().value());
        checksum += bench::digest(message.fields.consolidated_last_price.get().value());
        checksum += bench::digest(message.fields.consolidated_high_price.get().value());
        checksum += bench::digest(message.fields.consolidated_low_price.get().value());
        checksum += bench::digest(message.fields.consolidated_fractional_total_volume.get().value());
        checksum += bench::digest(message.fields.consolidated_tick.get().value());
        checksum += bench::digest(message.fields.participant_previous_close_price_date.get().value());
        checksum += bench::digest(message.fields.participant_last_price.get().value());
        checksum += bench::digest(message.fields.participant_high_price.get().value());
        checksum += bench::digest(message.fields.participant_low_price.get().value());
        checksum += bench::digest(message.fields.participant_open_price.get().value());
        checksum += bench::digest(message.fields.participant_fractional_total_volume.get().value());
        checksum += bench::digest(message.fields.participant_tick.get().value());
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
    return bench::run("Siac.Cts.Output.Cta.v2.11.b", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
