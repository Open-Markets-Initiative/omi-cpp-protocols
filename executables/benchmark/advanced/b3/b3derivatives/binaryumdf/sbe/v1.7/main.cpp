// B3.B3Derivatives.BinaryUmdf.Sbe.v1.7: main.cpp
// B3.B3Derivatives.BinaryUmdf.Sbe.v1.7 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/b3/b3derivatives/binaryumdf/sbe/v1.7.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/b3/b3derivatives/binaryumdf/sbe/v1.7/messages/session.hpp"

namespace protocol = ::b3::b3derivatives::binaryumdf::sbe::v1_7;

namespace {

// The handler the session layer hands each datagram's values to
struct Reader {
    std::uint64_t checksum = 0;
    std::size_t index = 0;

    protocol::seq_action on_transport_header(const protocol::packet_header& header, const packet::Frame&) {
        checksum += bench::digest(header.channel_id.get().value());
        checksum += bench::digest(header.sequence_version.get().value());
        checksum += bench::digest(header.sequence_number.get().value());
        checksum += bench::digest(header.sending_time.get().value());
        return protocol::seq_action::process;
    }

    // a message this test prints no values of still takes its entry
    template <typename Message>
    void on_message(const Message&, std::uint64_t, const protocol::packet_header&) {
        ++index;
    }

    void on_message(const protocol::sequence_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.next_seq_no.get().value());
    }

    void on_message(const protocol::empty_book_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::channel_reset_11_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::security_status_3_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.trading_session_id.get().value());
        checksum += bench::digest(message.fields.security_trading_status.get().value());
        checksum += (message.fields.security_trading_event.get().has_value() ? bench::digest(message.fields.security_trading_event.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += (message.fields.trad_ses_open_time.get().has_value() ? bench::digest(message.fields.trad_ses_open_time.get().value()) : std::uint64_t{0});
        checksum += (message.fields.transact_time.get().has_value() ? bench::digest(message.fields.transact_time.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::security_group_phase_10_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.trading_session_id.get().value());
        checksum += bench::digest(message.fields.trading_session_sub_id.get().value());
        checksum += (message.fields.security_trading_event.get().has_value() ? bench::digest(message.fields.security_trading_event.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += (message.fields.trad_ses_open_time.get().has_value() ? bench::digest(message.fields.trad_ses_open_time.get().value()) : std::uint64_t{0});
        checksum += (message.fields.transact_time.get().has_value() ? bench::digest(message.fields.transact_time.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::deprecated_security_definition_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_exchange.get().value());
        checksum += bench::digest(message.fields.security_id_source.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.security_update_action.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.security_sub_type.get().value());
        checksum += bench::digest(message.fields.tot_no_related_sym.get().value());
        checksum += (message.fields.min_price_increment_legacy.get().has_value() ? bench::digest(message.fields.min_price_increment_legacy.get().value()) : std::uint64_t{0});
        checksum += (message.fields.strike_price.get().has_value() ? bench::digest(message.fields.strike_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_multiplier.get().has_value() ? bench::digest(message.fields.contract_multiplier.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_divisor.get().has_value() ? bench::digest(message.fields.price_divisor.get().value()) : std::uint64_t{0});
        checksum += (message.fields.security_validity_timestamp.get().has_value() ? bench::digest(message.fields.security_validity_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.no_shares_issued.get().has_value() ? bench::digest(message.fields.no_shares_issued.get().value()) : std::uint64_t{0});
        checksum += (message.fields.clearing_house_id.get().has_value() ? bench::digest(message.fields.clearing_house_id.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_order_qty.get().has_value() ? bench::digest(message.fields.min_order_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.max_order_qty.get().has_value() ? bench::digest(message.fields.max_order_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_lot_size.get().has_value() ? bench::digest(message.fields.min_lot_size.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_trade_vol.get().has_value() ? bench::digest(message.fields.min_trade_vol.get().value()) : std::uint64_t{0});
        checksum += (message.fields.corporate_action_event_id.get().has_value() ? bench::digest(message.fields.corporate_action_event_id.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.issue_date.get().value());
        checksum += (message.fields.maturity_date.get().has_value() ? bench::digest(message.fields.maturity_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.start_date.get().has_value() ? bench::digest(message.fields.start_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.end_date.get().has_value() ? bench::digest(message.fields.end_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.settl_type.get().has_value() ? bench::digest(message.fields.settl_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.settl_date.get().has_value() ? bench::digest(message.fields.settl_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.dated_date.get().has_value() ? bench::digest(message.fields.dated_date.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.asset.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += (message.fields.maturity_month_year.year.get().has_value() ? bench::digest(message.fields.maturity_month_year.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.month.get().has_value() ? bench::digest(message.fields.maturity_month_year.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.day.get().has_value() ? bench::digest(message.fields.maturity_month_year.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.week.get().has_value() ? bench::digest(message.fields.maturity_month_year.week.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_settl_month.year.get().has_value() ? bench::digest(message.fields.contract_settl_month.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_settl_month.month.get().has_value() ? bench::digest(message.fields.contract_settl_month.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_settl_month.day.get().has_value() ? bench::digest(message.fields.contract_settl_month.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_settl_month.week.get().has_value() ? bench::digest(message.fields.contract_settl_month.week.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += (message.fields.lot_type.get().has_value() ? bench::digest(message.fields.lot_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.tick_size_denominator.get().has_value() ? bench::digest(message.fields.tick_size_denominator.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.product.get().value());
        checksum += (message.fields.exercise_style.get().has_value() ? bench::digest(message.fields.exercise_style.get().value()) : std::uint64_t{0});
        checksum += (message.fields.put_or_call.get().has_value() ? bench::digest(message.fields.put_or_call.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_type.get().has_value() ? bench::digest(message.fields.price_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.market_segment_id.get().has_value() ? bench::digest(message.fields.market_segment_id.get().value()) : std::uint64_t{0});
        checksum += (message.fields.governance_indicator.get().has_value() ? bench::digest(message.fields.governance_indicator.get().value()) : std::uint64_t{0});
        checksum += (message.fields.security_match_type.get().has_value() ? bench::digest(message.fields.security_match_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.last_fragment.get().has_value() ? bench::digest(message.fields.last_fragment.get().value()) : std::uint64_t{0});
        checksum += (message.fields.multi_leg_model.get().has_value() ? bench::digest(message.fields.multi_leg_model.get().value()) : std::uint64_t{0});
        checksum += (message.fields.multi_leg_price_method.get().has_value() ? bench::digest(message.fields.multi_leg_price_method.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_cross_qty.get().has_value() ? bench::digest(message.fields.min_cross_qty.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::security_definition_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.security_exchange.get().value());
        checksum += bench::digest(message.fields.security_id_source.get().value());
        checksum += bench::digest(message.fields.security_group.get().value());
        checksum += bench::digest(message.fields.symbol.get().value());
        checksum += bench::digest(message.fields.security_update_action.get().value());
        checksum += bench::digest(message.fields.security_type.get().value());
        checksum += bench::digest(message.fields.security_sub_type.get().value());
        checksum += bench::digest(message.fields.tot_no_related_sym.get().value());
        checksum += (message.fields.min_price_increment_optional.get().has_value() ? bench::digest(message.fields.min_price_increment_optional.get().value()) : std::uint64_t{0});
        checksum += (message.fields.strike_price.get().has_value() ? bench::digest(message.fields.strike_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_multiplier.get().has_value() ? bench::digest(message.fields.contract_multiplier.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_divisor.get().has_value() ? bench::digest(message.fields.price_divisor.get().value()) : std::uint64_t{0});
        checksum += (message.fields.security_validity_timestamp.get().has_value() ? bench::digest(message.fields.security_validity_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.no_shares_issued.get().has_value() ? bench::digest(message.fields.no_shares_issued.get().value()) : std::uint64_t{0});
        checksum += (message.fields.clearing_house_id.get().has_value() ? bench::digest(message.fields.clearing_house_id.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_order_qty.get().has_value() ? bench::digest(message.fields.min_order_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.max_order_qty.get().has_value() ? bench::digest(message.fields.max_order_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_lot_size.get().has_value() ? bench::digest(message.fields.min_lot_size.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_trade_vol.get().has_value() ? bench::digest(message.fields.min_trade_vol.get().value()) : std::uint64_t{0});
        checksum += (message.fields.corporate_action_event_id.get().has_value() ? bench::digest(message.fields.corporate_action_event_id.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.issue_date.get().value());
        checksum += (message.fields.maturity_date.get().has_value() ? bench::digest(message.fields.maturity_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.start_date.get().has_value() ? bench::digest(message.fields.start_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.end_date.get().has_value() ? bench::digest(message.fields.end_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.settl_type.get().has_value() ? bench::digest(message.fields.settl_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.settl_date.get().has_value() ? bench::digest(message.fields.settl_date.get().value()) : std::uint64_t{0});
        checksum += (message.fields.dated_date.get().has_value() ? bench::digest(message.fields.dated_date.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.asset.get().value());
        checksum += bench::digest(message.fields.cfi_code.get().value());
        checksum += (message.fields.maturity_month_year.year.get().has_value() ? bench::digest(message.fields.maturity_month_year.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.month.get().has_value() ? bench::digest(message.fields.maturity_month_year.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.day.get().has_value() ? bench::digest(message.fields.maturity_month_year.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.maturity_month_year.week.get().has_value() ? bench::digest(message.fields.maturity_month_year.week.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_settl_month.year.get().has_value() ? bench::digest(message.fields.contract_settl_month.year.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_settl_month.month.get().has_value() ? bench::digest(message.fields.contract_settl_month.month.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_settl_month.day.get().has_value() ? bench::digest(message.fields.contract_settl_month.day.get().value()) : std::uint64_t{0});
        checksum += (message.fields.contract_settl_month.week.get().has_value() ? bench::digest(message.fields.contract_settl_month.week.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.currency.get().value());
        checksum += (message.fields.lot_type.get().has_value() ? bench::digest(message.fields.lot_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.tick_size_denominator.get().has_value() ? bench::digest(message.fields.tick_size_denominator.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.product.get().value());
        checksum += (message.fields.exercise_style.get().has_value() ? bench::digest(message.fields.exercise_style.get().value()) : std::uint64_t{0});
        checksum += (message.fields.put_or_call.get().has_value() ? bench::digest(message.fields.put_or_call.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_type.get().has_value() ? bench::digest(message.fields.price_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.market_segment_id.get().has_value() ? bench::digest(message.fields.market_segment_id.get().value()) : std::uint64_t{0});
        checksum += (message.fields.governance_indicator.get().has_value() ? bench::digest(message.fields.governance_indicator.get().value()) : std::uint64_t{0});
        checksum += (message.fields.security_match_type.get().has_value() ? bench::digest(message.fields.security_match_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.last_fragment.get().has_value() ? bench::digest(message.fields.last_fragment.get().value()) : std::uint64_t{0});
        checksum += (message.fields.multi_leg_model.get().has_value() ? bench::digest(message.fields.multi_leg_model.get().value()) : std::uint64_t{0});
        checksum += (message.fields.multi_leg_price_method.get().has_value() ? bench::digest(message.fields.multi_leg_price_method.get().value()) : std::uint64_t{0});
        checksum += (message.fields.min_cross_qty.get().has_value() ? bench::digest(message.fields.min_cross_qty.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::news_5_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += (message.fields.security_id_optional.get().has_value() ? bench::digest(message.fields.security_id_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.news_source.get().value());
        checksum += bench::digest(message.fields.part_count.get().value());
        checksum += bench::digest(message.fields.part_number.get().value());
        checksum += (message.fields.news_id.get().has_value() ? bench::digest(message.fields.news_id.get().value()) : std::uint64_t{0});
        checksum += (message.fields.orig_time.get().has_value() ? bench::digest(message.fields.orig_time.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.total_text_length.get().value());
    }

    void on_message(const protocol::opening_price_15_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.md_update_action.get().value());
        checksum += bench::digest(message.fields.open_close_settl_flag.get().value());
        checksum += bench::digest(message.fields.md_future_price.get().value());
        checksum += (message.fields.net_chg_prev_day.get().has_value() ? bench::digest(message.fields.net_chg_prev_day.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::theoretical_opening_price_16_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.md_update_action.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += (message.fields.md_corporate_offset_price_optional.get().has_value() ? bench::digest(message.fields.md_corporate_offset_price_optional.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_size_optional.get().has_value() ? bench::digest(message.fields.md_entry_size_optional.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::closing_price_17_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.open_close_settl_flag.get().value());
        checksum += bench::digest(message.fields.md_corporate_price.get().value());
        checksum += (message.fields.last_trade_date.get().has_value() ? bench::digest(message.fields.last_trade_date.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::auction_imbalance_19_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.md_update_action.get().value());
        checksum += bench::digest(message.fields.imbalance_condition.has_imbalance_more_buyers());
        checksum += bench::digest(message.fields.imbalance_condition.has_imbalance_more_sellers());
        checksum += (message.fields.md_entry_size_optional.get().has_value() ? bench::digest(message.fields.md_entry_size_optional.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::price_band_20_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.price_band_type.get().has_value() ? bench::digest(message.fields.price_band_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_limit_type.get().has_value() ? bench::digest(message.fields.price_limit_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_band_midpoint_price_type.get().has_value() ? bench::digest(message.fields.price_band_midpoint_price_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price.get().has_value() ? bench::digest(message.fields.low_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price.get().has_value() ? bench::digest(message.fields.high_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trading_reference_price_legacy.get().has_value() ? bench::digest(message.fields.trading_reference_price_legacy.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::quantity_band_21_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.avg_daily_traded_qty.get().has_value() ? bench::digest(message.fields.avg_daily_traded_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.max_trade_vol.get().has_value() ? bench::digest(message.fields.max_trade_vol.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::price_band_22_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += (message.fields.price_band_type.get().has_value() ? bench::digest(message.fields.price_band_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_limit_type.get().has_value() ? bench::digest(message.fields.price_limit_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.price_band_midpoint_price_type.get().has_value() ? bench::digest(message.fields.price_band_midpoint_price_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.low_limit_price.get().has_value() ? bench::digest(message.fields.low_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.high_limit_price.get().has_value() ? bench::digest(message.fields.high_limit_price.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trading_reference_price_optional.get().has_value() ? bench::digest(message.fields.trading_reference_price_optional.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::high_price_24_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.md_update_action.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.md_future_price.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::low_price_25_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.md_update_action.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.md_future_price.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::last_trade_price_27_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.trading_session_id.get().value());
        checksum += bench::digest(message.fields.trade_condition.has_opening_price());
        checksum += bench::digest(message.fields.trade_condition.has_crossed());
        checksum += bench::digest(message.fields.trade_condition.has_last_trade_at_the_same_price());
        checksum += bench::digest(message.fields.trade_condition.has_out_of_sequence());
        checksum += bench::digest(message.fields.trade_condition.has_trade_on_behalf());
        checksum += bench::digest(message.fields.trade_condition.has_regular_trade());
        checksum += bench::digest(message.fields.trade_condition.has_block_trade());
        checksum += bench::digest(message.fields.md_future_price.get().value());
        checksum += bench::digest(message.fields.md_entry_size.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += (message.fields.md_entry_buyer.get().has_value() ? bench::digest(message.fields.md_entry_buyer.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_seller.get().has_value() ? bench::digest(message.fields.md_entry_seller.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
        checksum += (message.fields.seller_days.get().has_value() ? bench::digest(message.fields.seller_days.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_interest_rate.get().has_value() ? bench::digest(message.fields.md_entry_interest_rate.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trd_sub_type.get().has_value() ? bench::digest(message.fields.trd_sub_type.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::snapshot_full_refresh_header_30_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.last_msg_seq_num_processed.get().value());
        checksum += bench::digest(message.fields.tot_num_reports.get().value());
        checksum += bench::digest(message.fields.tot_num_bids.get().value());
        checksum += bench::digest(message.fields.tot_num_offers.get().value());
        checksum += bench::digest(message.fields.tot_num_stats.get().value());
        checksum += (message.fields.last_rpt_seq.get().has_value() ? bench::digest(message.fields.last_rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::order_mb_o_50_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.md_update_action.get().value());
        checksum += bench::digest(message.fields.md_entry_type.get().value());
        checksum += (message.fields.md_corporate_offset_price_optional.get().has_value() ? bench::digest(message.fields.md_corporate_offset_price_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.md_entry_size.get().value());
        checksum += bench::digest(message.fields.md_entry_position_no.get().value());
        checksum += (message.fields.entering_firm.get().has_value() ? bench::digest(message.fields.entering_firm.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_insert_timestamp.get().has_value() ? bench::digest(message.fields.md_insert_timestamp.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.secondary_order_id.get().value());
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::delete_order_mb_o_51_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.md_entry_type.get().value());
        checksum += bench::digest(message.fields.md_entry_position_no.get().value());
        checksum += (message.fields.md_entry_size_optional.get().has_value() ? bench::digest(message.fields.md_entry_size_optional.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.secondary_order_id.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::mass_delete_orders_mb_o_52_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.md_update_action.get().value());
        checksum += bench::digest(message.fields.md_entry_type.get().value());
        checksum += bench::digest(message.fields.md_entry_position_no.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::trade_53_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.trading_session_id.get().value());
        checksum += bench::digest(message.fields.trade_condition.has_opening_price());
        checksum += bench::digest(message.fields.trade_condition.has_crossed());
        checksum += bench::digest(message.fields.trade_condition.has_last_trade_at_the_same_price());
        checksum += bench::digest(message.fields.trade_condition.has_out_of_sequence());
        checksum += bench::digest(message.fields.trade_condition.has_trade_on_behalf());
        checksum += bench::digest(message.fields.trade_condition.has_regular_trade());
        checksum += bench::digest(message.fields.trade_condition.has_block_trade());
        checksum += bench::digest(message.fields.md_future_price.get().value());
        checksum += bench::digest(message.fields.md_entry_size.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += (message.fields.md_entry_buyer.get().has_value() ? bench::digest(message.fields.md_entry_buyer.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_seller.get().has_value() ? bench::digest(message.fields.md_entry_seller.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += (message.fields.trd_sub_type.get().has_value() ? bench::digest(message.fields.trd_sub_type.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::forward_trade_54_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.trading_session_id.get().value());
        checksum += bench::digest(message.fields.trade_condition.has_opening_price());
        checksum += bench::digest(message.fields.trade_condition.has_crossed());
        checksum += bench::digest(message.fields.trade_condition.has_last_trade_at_the_same_price());
        checksum += bench::digest(message.fields.trade_condition.has_out_of_sequence());
        checksum += bench::digest(message.fields.trade_condition.has_trade_on_behalf());
        checksum += bench::digest(message.fields.trade_condition.has_regular_trade());
        checksum += bench::digest(message.fields.trade_condition.has_block_trade());
        checksum += bench::digest(message.fields.md_future_price.get().value());
        checksum += bench::digest(message.fields.md_entry_size.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += (message.fields.md_entry_buyer.get().has_value() ? bench::digest(message.fields.md_entry_buyer.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_seller.get().has_value() ? bench::digest(message.fields.md_entry_seller.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
        checksum += (message.fields.seller_days.get().has_value() ? bench::digest(message.fields.seller_days.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_interest_rate.get().has_value() ? bench::digest(message.fields.md_entry_interest_rate.get().value()) : std::uint64_t{0});
        checksum += (message.fields.trd_sub_type.get().has_value() ? bench::digest(message.fields.trd_sub_type.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::execution_summary_55_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.aggressor_side.get().value());
        checksum += bench::digest(message.fields.last_px.get().value());
        checksum += bench::digest(message.fields.fill_qty.get().value());
        checksum += (message.fields.traded_hidden_qty.get().has_value() ? bench::digest(message.fields.traded_hidden_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.cxl_qty.get().has_value() ? bench::digest(message.fields.cxl_qty.get().value()) : std::uint64_t{0});
        checksum += (message.fields.aggressor_time.get().has_value() ? bench::digest(message.fields.aggressor_time.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::execution_statistics_56_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.trading_session_id.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += bench::digest(message.fields.trade_volume.get().value());
        checksum += (message.fields.vwap_px.get().has_value() ? bench::digest(message.fields.vwap_px.get().value()) : std::uint64_t{0});
        checksum += (message.fields.net_chg_prev_day.get().has_value() ? bench::digest(message.fields.net_chg_prev_day.get().value()) : std::uint64_t{0});
        checksum += bench::digest(message.fields.number_of_trades.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::trade_bust_57_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_trade_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_volume_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_quote_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_stats_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_last_implied_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_recovery_msg());
        checksum += bench::digest(message.fields.match_event_indicator.has_end_of_event());
        checksum += bench::digest(message.fields.trading_session_id.get().value());
        checksum += bench::digest(message.fields.md_future_price.get().value());
        checksum += bench::digest(message.fields.md_entry_size.get().value());
        checksum += bench::digest(message.fields.trade_id.get().value());
        checksum += bench::digest(message.fields.trade_date.get().value());
        checksum += (message.fields.md_entry_timestamp.get().has_value() ? bench::digest(message.fields.md_entry_timestamp.get().value()) : std::uint64_t{0});
        checksum += (message.fields.rpt_seq.get().has_value() ? bench::digest(message.fields.rpt_seq.get().value()) : std::uint64_t{0});
    }

    void on_message(const protocol::snapshot_full_refresh_orders_mb_o_71_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.encoding_type.get().value());
        checksum += bench::digest(message.fields.security_id.get().value());
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
    return bench::run("B3.B3Derivatives.BinaryUmdf.Sbe.v1.7", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
