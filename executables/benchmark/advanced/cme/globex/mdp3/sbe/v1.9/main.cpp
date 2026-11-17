// Cme.Globex.Mdp3.Sbe.v1.9: main.cpp
// Cme.Globex.Mdp3.Sbe.v1.9 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/cme/globex/mdp3/sbe/v1.9.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/cme/globex/mdp3/sbe/v1.9/messages/session.hpp"

namespace protocol = ::cme::mdp3::v9;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::binary_packet_header& header, const packet::Frame&) {
        checksum += bench::digest(header.packet_sequence_number.get().value());
        checksum += bench::digest(header.sending_time.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::binary_packet_header&) {
        ++index;
    }

    void on_message(const protocol::channel_reset& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::admin_login& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.heart_bt_int.get().value());
    }

    void on_message(const protocol::admin_logout& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.text.get().value());
    }

    void on_message(const protocol::md_instrument_definition_future_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.tot_num_reports_optional.get().has_value() ? bench::digest(message.fields.tot_num_reports_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.security_update_action.get().value());
        checksum += bench::digest(message.fields.last_update_time.get().value());
        checksum += (message.fields.md_security_trading_status.get().has_value() ? bench::digest(message.fields.md_security_trading_status.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.appl_id.get().value());
        checksum += bench::digest(message.fields.market_segment_id.get().value());
        checksum += bench::digest(message.fields.underlying_product.get().value());
        checksum += bench::digest(message.fields.security_exchange.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.asset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += (message.fields.maturity_month_year.year.get().has_value() ? bench::digest(message.fields.maturity_month_year.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.month.get().has_value() ? bench::digest(message.fields.maturity_month_year.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.day.get().has_value() ? bench::digest(message.fields.maturity_month_year.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.week.get().has_value() ? bench::digest(message.fields.maturity_month_year.week.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += bench::digest(message.fields.settl_currency.get().value());
        checksum += bench::digest(message.fields.match_algorithm.get().value());
        checksum += bench::digest(message.fields.min_trade_vol.get().value());
        checksum += bench::digest(message.fields.max_trade_vol.get().value());
        checksum += bench::digest(message.fields.min_price_increment.get().value());
        checksum += bench::digest(message.fields.display_factor.get().value());
        checksum += (message.fields.main_fraction.get().has_value() ? bench::digest(message.fields.main_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.sub_fraction.get().has_value() ? bench::digest(message.fields.sub_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_display_format.get().has_value() ? bench::digest(message.fields.price_display_format.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.unit_of_measure.get().value());
        checksum += (message.fields.unit_of_measure_qty.get().has_value() ? bench::digest(message.fields.unit_of_measure_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trading_reference_price.get().has_value() ? bench::digest(message.fields.trading_reference_price.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.settl_price_type.has_final_daily());
        checksum += bench::digest(message.fields.settl_price_type.has_actual());
        checksum += bench::digest(message.fields.settl_price_type.has_rounded());
        checksum += bench::digest(message.fields.settl_price_type.has_intraday());
        checksum += bench::digest(message.fields.settl_price_type.has_null_value());
        checksum += (message.fields.open_interest_qty.get().has_value() ? bench::digest(message.fields.open_interest_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.cleared_volume.get().has_value() ? bench::digest(message.fields.cleared_volume.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price.get().has_value() ? bench::digest(message.fields.high_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price.get().has_value() ? bench::digest(message.fields.low_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.max_price_variation.get().has_value() ? bench::digest(message.fields.max_price_variation.get().value()) : std::uint64_t{0});
        checksum += (message.fields.decay_quantity.get().has_value() ? bench::digest(message.fields.decay_quantity.get().value()) : std::uint64_t{0});
        checksum += (message.fields.decay_start_date.get().has_value() ? bench::digest(message.fields.decay_start_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.original_contract_size.get().has_value() ? bench::digest(message.fields.original_contract_size.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_multiplier.get().has_value() ? bench::digest(message.fields.contract_multiplier.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_multiplier_unit.get().has_value() ? bench::digest(message.fields.contract_multiplier_unit.get().value()) : std::uint64_t{0});
        checksum += (message.fields.flow_schedule_type.get().has_value() ? bench::digest(message.fields.flow_schedule_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_price_increment_amount.get().has_value() ? bench::digest(message.fields.min_price_increment_amount.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.user_defined_instrument.get().value());
        checksum += (message.fields.trading_reference_date.get().has_value() ? bench::digest(message.fields.trading_reference_date.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::md_instrument_definition_spread_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.tot_num_reports_optional.get().has_value() ? bench::digest(message.fields.tot_num_reports_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.security_update_action.get().value());
        checksum += bench::digest(message.fields.last_update_time.get().value());
        checksum += (message.fields.md_security_trading_status.get().has_value() ? bench::digest(message.fields.md_security_trading_status.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.appl_id.get().value());
        checksum += bench::digest(message.fields.market_segment_id.get().value());
        checksum += (message.fields.underlying_product_optional.get().has_value() ? bench::digest(message.fields.underlying_product_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.security_exchange.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.asset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += (message.fields.maturity_month_year.year.get().has_value() ? bench::digest(message.fields.maturity_month_year.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.month.get().has_value() ? bench::digest(message.fields.maturity_month_year.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.day.get().has_value() ? bench::digest(message.fields.maturity_month_year.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.week.get().has_value() ? bench::digest(message.fields.maturity_month_year.week.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += bench::digest(message.fields.security_sub_type.get().value());
        checksum += bench::digest(message.fields.user_defined_instrument.get().value());
        checksum += bench::digest(message.fields.match_algorithm.get().value());
        checksum += bench::digest(message.fields.min_trade_vol.get().value());
        checksum += bench::digest(message.fields.max_trade_vol.get().value());
        checksum += bench::digest(message.fields.min_price_increment.get().value());
        checksum += bench::digest(message.fields.display_factor.get().value());
        checksum += (message.fields.price_display_format.get().has_value() ? bench::digest(message.fields.price_display_format.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_ratio.get().has_value() ? bench::digest(message.fields.price_ratio.get().value()) : std::uint64_t{0});
        checksum += (message.fields.tick_rule.get().has_value() ? bench::digest(message.fields.tick_rule.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.unit_of_measure.get().value());
        checksum += (message.fields.trading_reference_price.get().has_value() ? bench::digest(message.fields.trading_reference_price.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.settl_price_type.has_final_daily());
        checksum += bench::digest(message.fields.settl_price_type.has_actual());
        checksum += bench::digest(message.fields.settl_price_type.has_rounded());
        checksum += bench::digest(message.fields.settl_price_type.has_intraday());
        checksum += bench::digest(message.fields.settl_price_type.has_null_value());
        checksum += (message.fields.open_interest_qty.get().has_value() ? bench::digest(message.fields.open_interest_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.cleared_volume.get().has_value() ? bench::digest(message.fields.cleared_volume.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price.get().has_value() ? bench::digest(message.fields.high_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price.get().has_value() ? bench::digest(message.fields.low_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.max_price_variation.get().has_value() ? bench::digest(message.fields.max_price_variation.get().value()) : std::uint64_t{0});
        checksum += (message.fields.main_fraction.get().has_value() ? bench::digest(message.fields.main_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.sub_fraction.get().has_value() ? bench::digest(message.fields.sub_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trading_reference_date.get().has_value() ? bench::digest(message.fields.trading_reference_date.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::security_status& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.asset.get().value());
        checksum += (message.fields.security_id_optional.get().has_value() ? bench::digest(message.fields.security_id_optional.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trade_date.get().has_value() ? bench::digest(message.fields.trade_date.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.security_trading_status.get().has_value() ? bench::digest(message.fields.security_trading_status.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.halt_reason.get().value());
        checksum += bench::digest(message.fields.security_trading_event.get().value());
    }

    void on_message(const protocol::md_incremental_refresh_book_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_daily_statistics_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_limits_banding_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_session_statistics_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_volume& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::snapshot_full_refresh_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.last_msg_seq_num_processed.get().value());
        checksum += bench::digest(message.fields.tot_num_reports.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.rpt_seq.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.last_update_time.get().value());
        checksum += (message.fields.trade_date.get().has_value() ? bench::digest(message.fields.trade_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_security_trading_status.get().has_value() ? bench::digest(message.fields.md_security_trading_status.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price.get().has_value() ? bench::digest(message.fields.high_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price.get().has_value() ? bench::digest(message.fields.low_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.max_price_variation.get().has_value() ? bench::digest(message.fields.max_price_variation.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::quote_request& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.quote_req_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_instrument_definition_option_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.tot_num_reports_optional.get().has_value() ? bench::digest(message.fields.tot_num_reports_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.security_update_action.get().value());
        checksum += bench::digest(message.fields.last_update_time.get().value());
        checksum += (message.fields.md_security_trading_status.get().has_value() ? bench::digest(message.fields.md_security_trading_status.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.appl_id.get().value());
        checksum += bench::digest(message.fields.market_segment_id.get().value());
        checksum += bench::digest(message.fields.underlying_product.get().value());
        checksum += bench::digest(message.fields.security_exchange.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.asset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += bench::digest(message.fields.put_or_call.get().value());
        checksum += (message.fields.maturity_month_year.year.get().has_value() ? bench::digest(message.fields.maturity_month_year.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.month.get().has_value() ? bench::digest(message.fields.maturity_month_year.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.day.get().has_value() ? bench::digest(message.fields.maturity_month_year.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.week.get().has_value() ? bench::digest(message.fields.maturity_month_year.week.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += (message.fields.strike_price.get().has_value() ? bench::digest(message.fields.strike_price.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.strike_currency.get().value());
        checksum += bench::digest(message.fields.settl_currency.get().value());
        checksum += (message.fields.min_cab_price.get().has_value() ? bench::digest(message.fields.min_cab_price.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.match_algorithm.get().value());
        checksum += bench::digest(message.fields.min_trade_vol.get().value());
        checksum += bench::digest(message.fields.max_trade_vol.get().value());
        checksum += (message.fields.min_price_increment_optional.get().has_value() ? bench::digest(message.fields.min_price_increment_optional.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_price_increment_amount.get().has_value() ? bench::digest(message.fields.min_price_increment_amount.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.display_factor.get().value());
        checksum += (message.fields.tick_rule.get().has_value() ? bench::digest(message.fields.tick_rule.get().value()) : std::uint64_t{0});
        checksum += (message.fields.main_fraction.get().has_value() ? bench::digest(message.fields.main_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.sub_fraction.get().has_value() ? bench::digest(message.fields.sub_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_display_format.get().has_value() ? bench::digest(message.fields.price_display_format.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.unit_of_measure.get().value());
        checksum += (message.fields.unit_of_measure_qty.get().has_value() ? bench::digest(message.fields.unit_of_measure_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trading_reference_price.get().has_value() ? bench::digest(message.fields.trading_reference_price.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.settl_price_type.has_final_daily());
        checksum += bench::digest(message.fields.settl_price_type.has_actual());
        checksum += bench::digest(message.fields.settl_price_type.has_rounded());
        checksum += bench::digest(message.fields.settl_price_type.has_intraday());
        checksum += bench::digest(message.fields.settl_price_type.has_null_value());
        checksum += (message.fields.cleared_volume.get().has_value() ? bench::digest(message.fields.cleared_volume.get().value()) : std::uint64_t{0});
        checksum += (message.fields.open_interest_qty.get().has_value() ? bench::digest(message.fields.open_interest_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price.get().has_value() ? bench::digest(message.fields.low_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price.get().has_value() ? bench::digest(message.fields.high_limit_price.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.user_defined_instrument.get().value());
        checksum += (message.fields.trading_reference_date.get().has_value() ? bench::digest(message.fields.trading_reference_date.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::md_incremental_refresh_trade_summary_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_order_book_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::snapshot_full_refresh_order_book_legacy& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.last_msg_seq_num_processed.get().value());
        checksum += bench::digest(message.fields.tot_num_reports.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.no_chunks.get().value());
        checksum += bench::digest(message.fields.current_chunk.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
    }

    void on_message(const protocol::md_incremental_refresh_book& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_order_book& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_trade_summary& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_daily_statistics& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_limits_banding& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::md_incremental_refresh_session_statistics& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
    }

    void on_message(const protocol::snapshot_full_refresh& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.last_msg_seq_num_processed.get().value());
        checksum += bench::digest(message.fields.tot_num_reports.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.rpt_seq.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
        checksum += bench::digest(message.fields.last_update_time.get().value());
        checksum += (message.fields.trade_date.get().has_value() ? bench::digest(message.fields.trade_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_security_trading_status.get().has_value() ? bench::digest(message.fields.md_security_trading_status.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price_ex.get().has_value() ? bench::digest(message.fields.high_limit_price_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price_ex.get().has_value() ? bench::digest(message.fields.low_limit_price_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.max_price_variation_ex.get().has_value() ? bench::digest(message.fields.max_price_variation_ex.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::snapshot_full_refresh_order_book& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.last_msg_seq_num_processed.get().value());
        checksum += bench::digest(message.fields.tot_num_reports.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.no_chunks.get().value());
        checksum += bench::digest(message.fields.current_chunk.get().value());
        checksum += bench::digest(message.fields.transact_time.get().value());
    }

    void on_message(const protocol::md_instrument_definition_future& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.tot_num_reports_optional.get().has_value() ? bench::digest(message.fields.tot_num_reports_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.security_update_action.get().value());
        checksum += bench::digest(message.fields.last_update_time.get().value());
        checksum += (message.fields.md_security_trading_status.get().has_value() ? bench::digest(message.fields.md_security_trading_status.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.appl_id.get().value());
        checksum += bench::digest(message.fields.market_segment_id.get().value());
        checksum += bench::digest(message.fields.underlying_product.get().value());
        checksum += bench::digest(message.fields.security_exchange.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.asset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += (message.fields.maturity_month_year.year.get().has_value() ? bench::digest(message.fields.maturity_month_year.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.month.get().has_value() ? bench::digest(message.fields.maturity_month_year.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.day.get().has_value() ? bench::digest(message.fields.maturity_month_year.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.week.get().has_value() ? bench::digest(message.fields.maturity_month_year.week.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += bench::digest(message.fields.settl_currency.get().value());
        checksum += bench::digest(message.fields.match_algorithm.get().value());
        checksum += bench::digest(message.fields.min_trade_vol.get().value());
        checksum += bench::digest(message.fields.max_trade_vol.get().value());
        checksum += bench::digest(message.fields.min_price_increment_ex.get().value());
        checksum += bench::digest(message.fields.display_factor_ex.get().value());
        checksum += (message.fields.main_fraction.get().has_value() ? bench::digest(message.fields.main_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.sub_fraction.get().has_value() ? bench::digest(message.fields.sub_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_display_format.get().has_value() ? bench::digest(message.fields.price_display_format.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.unit_of_measure.get().value());
        checksum += (message.fields.unit_of_measure_qty_ex.get().has_value() ? bench::digest(message.fields.unit_of_measure_qty_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trading_reference_price_ex.get().has_value() ? bench::digest(message.fields.trading_reference_price_ex.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.settl_price_type.has_final_daily());
        checksum += bench::digest(message.fields.settl_price_type.has_actual());
        checksum += bench::digest(message.fields.settl_price_type.has_rounded());
        checksum += bench::digest(message.fields.settl_price_type.has_intraday());
        checksum += bench::digest(message.fields.settl_price_type.has_null_value());
        checksum += (message.fields.open_interest_qty.get().has_value() ? bench::digest(message.fields.open_interest_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.cleared_volume.get().has_value() ? bench::digest(message.fields.cleared_volume.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price_ex.get().has_value() ? bench::digest(message.fields.high_limit_price_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price_ex.get().has_value() ? bench::digest(message.fields.low_limit_price_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.max_price_variation_ex.get().has_value() ? bench::digest(message.fields.max_price_variation_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.decay_quantity.get().has_value() ? bench::digest(message.fields.decay_quantity.get().value()) : std::uint64_t{0});
        checksum += (message.fields.decay_start_date.get().has_value() ? bench::digest(message.fields.decay_start_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.original_contract_size.get().has_value() ? bench::digest(message.fields.original_contract_size.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_multiplier.get().has_value() ? bench::digest(message.fields.contract_multiplier.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_multiplier_unit.get().has_value() ? bench::digest(message.fields.contract_multiplier_unit.get().value()) : std::uint64_t{0});
        checksum += (message.fields.flow_schedule_type.get().has_value() ? bench::digest(message.fields.flow_schedule_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_price_increment_amount_ex.get().has_value() ? bench::digest(message.fields.min_price_increment_amount_ex.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.user_defined_instrument.get().value());
        checksum += (message.fields.trading_reference_date.get().has_value() ? bench::digest(message.fields.trading_reference_date.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::md_instrument_definition_option& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.tot_num_reports_optional.get().has_value() ? bench::digest(message.fields.tot_num_reports_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.security_update_action.get().value());
        checksum += bench::digest(message.fields.last_update_time.get().value());
        checksum += (message.fields.md_security_trading_status.get().has_value() ? bench::digest(message.fields.md_security_trading_status.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.appl_id.get().value());
        checksum += bench::digest(message.fields.market_segment_id.get().value());
        checksum += bench::digest(message.fields.underlying_product.get().value());
        checksum += bench::digest(message.fields.security_exchange.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.asset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += bench::digest(message.fields.put_or_call.get().value());
        checksum += (message.fields.maturity_month_year.year.get().has_value() ? bench::digest(message.fields.maturity_month_year.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.month.get().has_value() ? bench::digest(message.fields.maturity_month_year.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.day.get().has_value() ? bench::digest(message.fields.maturity_month_year.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.week.get().has_value() ? bench::digest(message.fields.maturity_month_year.week.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += (message.fields.strike_price_ex.get().has_value() ? bench::digest(message.fields.strike_price_ex.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.strike_currency.get().value());
        checksum += bench::digest(message.fields.settl_currency.get().value());
        checksum += (message.fields.min_cab_price_ex.get().has_value() ? bench::digest(message.fields.min_cab_price_ex.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.match_algorithm.get().value());
        checksum += bench::digest(message.fields.min_trade_vol.get().value());
        checksum += bench::digest(message.fields.max_trade_vol.get().value());
        checksum += (message.fields.min_price_increment_optional_ex.get().has_value() ? bench::digest(message.fields.min_price_increment_optional_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_price_increment_amount_ex.get().has_value() ? bench::digest(message.fields.min_price_increment_amount_ex.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.display_factor_ex.get().value());
        checksum += (message.fields.tick_rule.get().has_value() ? bench::digest(message.fields.tick_rule.get().value()) : std::uint64_t{0});
        checksum += (message.fields.main_fraction.get().has_value() ? bench::digest(message.fields.main_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.sub_fraction.get().has_value() ? bench::digest(message.fields.sub_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_display_format.get().has_value() ? bench::digest(message.fields.price_display_format.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.unit_of_measure.get().value());
        checksum += (message.fields.unit_of_measure_qty_ex.get().has_value() ? bench::digest(message.fields.unit_of_measure_qty_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trading_reference_price_ex.get().has_value() ? bench::digest(message.fields.trading_reference_price_ex.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.settl_price_type.has_final_daily());
        checksum += bench::digest(message.fields.settl_price_type.has_actual());
        checksum += bench::digest(message.fields.settl_price_type.has_rounded());
        checksum += bench::digest(message.fields.settl_price_type.has_intraday());
        checksum += bench::digest(message.fields.settl_price_type.has_null_value());
        checksum += (message.fields.cleared_volume.get().has_value() ? bench::digest(message.fields.cleared_volume.get().value()) : std::uint64_t{0});
        checksum += (message.fields.open_interest_qty.get().has_value() ? bench::digest(message.fields.open_interest_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price_ex.get().has_value() ? bench::digest(message.fields.low_limit_price_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price_ex.get().has_value() ? bench::digest(message.fields.high_limit_price_ex.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.user_defined_instrument.get().value());
        checksum += (message.fields.trading_reference_date.get().has_value() ? bench::digest(message.fields.trading_reference_date.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::md_instrument_definition_spread& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.tot_num_reports_optional.get().has_value() ? bench::digest(message.fields.tot_num_reports_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.security_update_action.get().value());
        checksum += bench::digest(message.fields.last_update_time.get().value());
        checksum += (message.fields.md_security_trading_status.get().has_value() ? bench::digest(message.fields.md_security_trading_status.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.appl_id.get().value());
        checksum += bench::digest(message.fields.market_segment_id.get().value());
        checksum += (message.fields.underlying_product_optional.get().has_value() ? bench::digest(message.fields.underlying_product_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.security_exchange.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.asset.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += (message.fields.maturity_month_year.year.get().has_value() ? bench::digest(message.fields.maturity_month_year.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.month.get().has_value() ? bench::digest(message.fields.maturity_month_year.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.day.get().has_value() ? bench::digest(message.fields.maturity_month_year.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.week.get().has_value() ? bench::digest(message.fields.maturity_month_year.week.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += bench::digest(message.fields.security_sub_type.get().value());
        checksum += bench::digest(message.fields.user_defined_instrument.get().value());
        checksum += bench::digest(message.fields.match_algorithm.get().value());
        checksum += bench::digest(message.fields.min_trade_vol.get().value());
        checksum += bench::digest(message.fields.max_trade_vol.get().value());
        checksum += (message.fields.min_price_increment_optional_ex.get().has_value() ? bench::digest(message.fields.min_price_increment_optional_ex.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.display_factor_ex.get().value());
        checksum += (message.fields.price_display_format.get().has_value() ? bench::digest(message.fields.price_display_format.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_ratio_ex.get().has_value() ? bench::digest(message.fields.price_ratio_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.tick_rule.get().has_value() ? bench::digest(message.fields.tick_rule.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.unit_of_measure.get().value());
        checksum += (message.fields.trading_reference_price_ex.get().has_value() ? bench::digest(message.fields.trading_reference_price_ex.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.settl_price_type.has_final_daily());
        checksum += bench::digest(message.fields.settl_price_type.has_actual());
        checksum += bench::digest(message.fields.settl_price_type.has_rounded());
        checksum += bench::digest(message.fields.settl_price_type.has_intraday());
        checksum += bench::digest(message.fields.settl_price_type.has_null_value());
        checksum += (message.fields.open_interest_qty.get().has_value() ? bench::digest(message.fields.open_interest_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.cleared_volume.get().has_value() ? bench::digest(message.fields.cleared_volume.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price_ex.get().has_value() ? bench::digest(message.fields.high_limit_price_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price_ex.get().has_value() ? bench::digest(message.fields.low_limit_price_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.max_price_variation_ex.get().has_value() ? bench::digest(message.fields.max_price_variation_ex.get().value()) : std::uint64_t{0});
        checksum += (message.fields.main_fraction.get().has_value() ? bench::digest(message.fields.main_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.sub_fraction.get().has_value() ? bench::digest(message.fields.sub_fraction.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trading_reference_date.get().has_value() ? bench::digest(message.fields.trading_reference_date.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::negotiate& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.hmac_signature.get().value());
        checksum += bench::digest(message.fields.access_key_id.get().value());
        checksum += bench::digest(message.fields.uuid.get().value());
        checksum += bench::digest(message.fields.request_timestamp.get().value());
        checksum += bench::digest(message.fields.session.get().value());
        checksum += bench::digest(message.fields.firm.get().value());
    }

    void on_message(const protocol::negotiation_reject& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.reason.get().value());
        checksum += bench::digest(message.fields.uuid.get().value());
        checksum += bench::digest(message.fields.request_timestamp.get().value());
        checksum += bench::digest(message.fields.error_codes.get().value());
    }

    void on_message(const protocol::negotiation_response& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.uuid.get().value());
        checksum += bench::digest(message.fields.request_timestamp.get().value());
        checksum += (message.fields.secret_key_secure_id_expiration.get().has_value() ? bench::digest(message.fields.secret_key_secure_id_expiration.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::terminate& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.reason.get().value());
        checksum += bench::digest(message.fields.uuid.get().value());
        checksum += bench::digest(message.fields.request_timestamp.get().value());
        checksum += bench::digest(message.fields.error_codes.get().value());
    }

    void on_message(const protocol::market_data_request& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.md_req_id.get().value());
        checksum += bench::digest(message.fields.subscription_req_type.get().value());
    }

    void on_message(const protocol::request_ack& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.md_req_id.get().value());
        checksum += bench::digest(message.fields.subscription_req_type.get().value());
        checksum += bench::digest(message.fields.md_req_id_status.get().value());
    }

    void on_message(const protocol::request_reject& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += (message.fields.md_req_id_optional.get().has_value() ? bench::digest(message.fields.md_req_id_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.md_req_rej_reason.get().value());
        checksum += bench::digest(message.fields.session_text.get().value());
    }

    void on_message(const protocol::security_list_request& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.md_req_id.get().value());
        checksum += bench::digest(message.fields.subscription_req_type.get().value());
    }

    void on_message(const protocol::security_status_request& message, std::uint64_t, const protocol::binary_packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_size.get().value());
        checksum += bench::digest(message.header.simple_binary_header.block_length.get().value());
        checksum += bench::digest(message.header.simple_binary_header.template_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.schema_id.get().value());
        checksum += bench::digest(message.header.simple_binary_header.version.get().value());
        checksum += bench::digest(message.fields.md_req_id.get().value());
        checksum += bench::digest(message.fields.subscription_req_type.get().value());
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
    return bench::run("Cme.Globex.Mdp3.Sbe.v1.9", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
