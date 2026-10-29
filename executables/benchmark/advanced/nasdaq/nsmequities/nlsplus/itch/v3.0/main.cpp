// Nasdaq.NsmEquities.NlsPlus.Itch.v3.0 benchmark, through the Advanced session layer: every value it reads from every message of the simulated
// sequence (tests/simulated/nasdaq/nsmequities/nlsplus/itch/v3.0.pcap), folded into a checksum and timed by executables/benchmark/Benchmark.hpp.

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
#include "cpp/binary/advanced/nasdaq/nsmequities/nlsplus/itch/v3.0/messages/session.hpp"

namespace protocol = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

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

    void on_message(const protocol::system_event_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.event_code.get().value());
    }

    void on_message(const protocol::trade_report_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.originating_market_center_identifier.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.trade_control_number.get().value());
        checksum += bench::digest(message.fields.trade_price.get().value());
        checksum += bench::digest(message.fields.trade_size.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.settlement_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.special_sale_condition.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::long_form_trade_report_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.originating_market_center_identifier.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.trade_control_number.get().value());
        checksum += bench::digest(message.fields.trade_price_long.get().value());
        checksum += bench::digest(message.fields.trade_size.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.settlement_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.special_sale_condition.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::next_shares_trade_report_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.originating_market_center_identifier.get().value());
        checksum += bench::digest(message.fields.next_shares_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.trade_control_number.get().value());
        checksum += bench::digest(message.fields.proxy_price.get().value());
        checksum += bench::digest(message.fields.trade_size.get().value());
        checksum += bench::digest(message.fields.nav_offset_amount.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.settlement_type.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.sale_condition_modifier.special_sale_condition.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::trade_cancel_error_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.originating_market_center_identifier.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.original_trade_control_number.get().value());
        checksum += bench::digest(message.fields.original_trade_price.get().value());
        checksum += bench::digest(message.fields.original_trade_size.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_settlement_type.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::long_form_trade_cancel_error_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.originating_market_center_identifier.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.original_trade_control_number.get().value());
        checksum += bench::digest(message.fields.original_trade_price_long.get().value());
        checksum += bench::digest(message.fields.original_trade_size.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_settlement_type.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::next_shares_trade_cancel_error_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.market_center.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.original_trade_control_number.get().value());
        checksum += bench::digest(message.fields.original_proxy_price.get().value());
        checksum += bench::digest(message.fields.original_nav_offset_amount.get().value());
        checksum += bench::digest(message.fields.original_trade_size.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_settlement_type.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::trade_correction_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.originating_market_center_identifier.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.original_trade_control_number.get().value());
        checksum += bench::digest(message.fields.original_trade_price.get().value());
        checksum += bench::digest(message.fields.original_trade_size.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_settlement_type.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value());
        checksum += bench::digest(message.fields.corrected_trade_control_number.get().value());
        checksum += bench::digest(message.fields.corrected_trade_price.get().value());
        checksum += bench::digest(message.fields.corrected_trade_size.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_settlement_type.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_special_sale_condition.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::long_form_trade_correction_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.originating_market_center_identifier.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.original_trade_control_number.get().value());
        checksum += bench::digest(message.fields.original_trade_price_long.get().value());
        checksum += bench::digest(message.fields.original_trade_size.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_settlement_type.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value());
        checksum += bench::digest(message.fields.corrected_trade_control_number.get().value());
        checksum += bench::digest(message.fields.corrected_trade_price_long.get().value());
        checksum += bench::digest(message.fields.corrected_trade_size.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_settlement_type.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_special_sale_condition.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::next_shares_trade_correction_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.market_center.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.original_trade_control_number.get().value());
        checksum += bench::digest(message.fields.original_proxy_price.get().value());
        checksum += bench::digest(message.fields.original_nav_offset_amount.get().value());
        checksum += bench::digest(message.fields.original_trade_size.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_settlement_type.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.original_sale_condition_modifier.original_special_sale_condition.get().value());
        checksum += bench::digest(message.fields.corrected_trade_control_number.get().value());
        checksum += bench::digest(message.fields.corrected_proxy_price.get().value());
        checksum += bench::digest(message.fields.corrected_nav_offset_amount.get().value());
        checksum += bench::digest(message.fields.corrected_trade_size.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_settlement_type.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_trade_through_exemption.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get().value());
        checksum += bench::digest(message.fields.corrected_sale_condition_modifier.corrected_special_sale_condition.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
    }

    void on_message(const protocol::stock_trading_action_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.reserved.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.current_trading_state.get().value());
        checksum += bench::digest(message.fields.reason.get().value());
    }

    void on_message(const protocol::stock_directory_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.market_category.get().value());
        checksum += bench::digest(message.fields.financial_status_indicator.get().value());
        checksum += bench::digest(message.fields.round_lot_size.get().value());
        checksum += bench::digest(message.fields.round_lots_only.get().value());
        checksum += bench::digest(message.fields.issue_classification.get().value());
        checksum += bench::digest(message.fields.issue_sub_type.get().value());
        checksum += bench::digest(message.fields.authenticity.get().value());
        checksum += bench::digest(message.fields.short_sale_threshold_indicator.get().value());
        checksum += bench::digest(message.fields.ipo_flag.get().value());
        checksum += bench::digest(message.fields.luld_reference_price_tier.get().value());
        checksum += bench::digest(message.fields.etp_flag.get().value());
        checksum += bench::digest(message.fields.etp_leverage_factor.get().value());
        checksum += bench::digest(message.fields.inverse_indicator.get().value());
        checksum += bench::digest(message.fields.bloomberg_id.get().value());
    }

    void on_message(const protocol::reg_sho_short_sale_price_test_restricted_indicator_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.reg_sho_action.get().value());
    }

    void on_message(const protocol::adjusted_closing_price_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.adjusted_closing_price.get().value());
    }

    void on_message(const protocol::long_form_adjusted_closing_price_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.adjusted_closing_price_long.get().value());
    }

    void on_message(const protocol::end_of_day_trade_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.market_category.get().value());
        checksum += bench::digest(message.fields.consolidated_high_price.get().value());
        checksum += bench::digest(message.fields.consolidated_low_price.get().value());
        checksum += bench::digest(message.fields.consolidated_closing_price.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
        checksum += bench::digest(message.fields.consolidated_open_price.get().value());
    }

    void on_message(const protocol::long_form_end_of_day_trade_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.market_category.get().value());
        checksum += bench::digest(message.fields.consolidated_high_price_long.get().value());
        checksum += bench::digest(message.fields.consolidated_low_price_long.get().value());
        checksum += bench::digest(message.fields.consolidated_closing_price_long.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
        checksum += bench::digest(message.fields.consolidated_open_price_long.get().value());
    }

    void on_message(const protocol::next_shares_end_of_day_trade_summary_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.market_category.get().value());
        checksum += bench::digest(message.fields.consolidated_high_price.get().value());
        checksum += bench::digest(message.fields.nav_offset_amount_high.get().value());
        checksum += bench::digest(message.fields.consolidated_low_price.get().value());
        checksum += bench::digest(message.fields.nav_offset_amount_low.get().value());
        checksum += bench::digest(message.fields.consolidated_closing_price.get().value());
        checksum += bench::digest(message.fields.nav_offset_amount_closing.get().value());
        checksum += bench::digest(message.fields.consolidated_volume.get().value());
        checksum += bench::digest(message.fields.consolidated_open_price.get().value());
        checksum += bench::digest(message.fields.nav_offset_amount_open.get().value());
    }

    void on_message(const protocol::ipo_information_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.issue_symbol.get().value());
        checksum += bench::digest(message.fields.security_class.get().value());
        checksum += bench::digest(message.fields.reference_for_net_change.get().value());
        checksum += bench::digest(message.fields.reference_price.get().value());
    }

    void on_message(const protocol::mwcb_decline_level_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.level_1.get().value());
        checksum += bench::digest(message.fields.level_2.get().value());
        checksum += bench::digest(message.fields.level_3.get().value());
    }

    void on_message(const protocol::mwcb_status_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.breached_level.get().value());
    }

    void on_message(const protocol::ipo_quoting_period_update_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.ipo_quotation_release_time.get().value());
        checksum += bench::digest(message.fields.ipo_quotation_release_qualifier.get().value());
        checksum += bench::digest(message.fields.ipo_price.get().value());
    }

    void on_message(const protocol::operational_halt_message& message, std::uint64_t, const protocol::packet_header&) {
        checksum += index++;
        checksum += bench::digest(message.header.message_length.get().value());
        checksum += bench::digest(message.header.tracking_number.get().value());
        checksum += bench::digest(message.header.timestamp.get().value());
        checksum += bench::digest(message.header.message_type.get().value());
        checksum += bench::digest(message.fields.stock.get().value());
        checksum += bench::digest(message.fields.market_code.get().value());
        checksum += bench::digest(message.fields.operational_halt_action.get().value());
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
    return bench::run("Nasdaq.NsmEquities.NlsPlus.Itch.v3.0", "advanced", argc, argv, [](const packet::Frame& frame) { return read(frame); });
}
