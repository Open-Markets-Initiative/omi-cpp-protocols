#pragma once

#include <ostream>
#include <string_view>

#include "SystemEventMessage.hpp"
#include "TradeReportMessage.hpp"
#include "LongFormTradeReportMessage.hpp"
#include "NextSharesTradeReportMessage.hpp"
#include "TradeCancelErrorMessage.hpp"
#include "LongFormTradeCancelErrorMessage.hpp"
#include "NextSharesTradeCancelErrorMessage.hpp"
#include "TradeCorrectionMessage.hpp"
#include "LongFormTradeCorrectionMessage.hpp"
#include "NextSharesTradeCorrectionMessage.hpp"
#include "StockTradingActionMessage.hpp"
#include "StockDirectoryMessage.hpp"
#include "RegShoShortSalePriceTestRestrictedIndicatorMessage.hpp"
#include "AdjustedClosingPriceMessage.hpp"
#include "LongFormAdjustedClosingPriceMessage.hpp"
#include "EndOfDayTradeSummaryMessage.hpp"
#include "LongFormEndOfDayTradeSummaryMessage.hpp"
#include "NextSharesEndOfDayTradeSummaryMessage.hpp"
#include "IpoInformationMessage.hpp"
#include "MwcbDeclineLevelMessage.hpp"
#include "MwcbStatusMessage.hpp"
#include "IpoQuotingPeriodUpdateMessage.hpp"
#include "OperationalHaltMessage.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

namespace itch_nlsplus = ::nasdaq::nsmequities::nlsplus::itch::v3_0;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "session=\"" << value.session.get_trimmed().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",message_count=" << value.message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",tracking_number=" << value.tracking_number.get().value()
       << ",timestamp=" << value.timestamp.get().value()
       << ",message_type=\"" << itch_nlsplus::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "event_code=\"" << itch_nlsplus::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_report_message& msg) {
    os << "originating_market_center_identifier=\"" << itch_nlsplus::originating_market_center_identifier::to_string(msg.fields.originating_market_center_identifier.get().value()) << '"'
       << ",issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",trade_control_number=\"" << msg.fields.trade_control_number.get_trimmed().value() << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",trade_size=" << msg.fields.trade_size.get().value()
       << ",sale_condition_modifier.settlement_type=\"" << itch_nlsplus::settlement_type::to_string(msg.fields.sale_condition_modifier.settlement_type.get().value()) << '"'
       << ",sale_condition_modifier.trade_through_exemption=\"" << itch_nlsplus::trade_through_exemption::to_string(msg.fields.sale_condition_modifier.trade_through_exemption.get().value()) << '"'
       << ",sale_condition_modifier.extended_hours_or_sold_code=\"" << itch_nlsplus::extended_hours_or_sold_code::to_string(msg.fields.sale_condition_modifier.extended_hours_or_sold_code.get().value()) << '"'
       << ",sale_condition_modifier.special_sale_condition=\"" << itch_nlsplus::special_sale_condition::to_string(msg.fields.sale_condition_modifier.special_sale_condition.get().value()) << '"'
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_form_trade_report_message& msg) {
    os << "originating_market_center_identifier=\"" << itch_nlsplus::originating_market_center_identifier::to_string(msg.fields.originating_market_center_identifier.get().value()) << '"'
       << ",issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",trade_control_number=\"" << msg.fields.trade_control_number.get_trimmed().value() << '"'
       << ",trade_price_long=" << msg.fields.trade_price_long.get().value()
       << ",trade_size=" << msg.fields.trade_size.get().value()
       << ",sale_condition_modifier.settlement_type=\"" << itch_nlsplus::settlement_type::to_string(msg.fields.sale_condition_modifier.settlement_type.get().value()) << '"'
       << ",sale_condition_modifier.trade_through_exemption=\"" << itch_nlsplus::trade_through_exemption::to_string(msg.fields.sale_condition_modifier.trade_through_exemption.get().value()) << '"'
       << ",sale_condition_modifier.extended_hours_or_sold_code=\"" << itch_nlsplus::extended_hours_or_sold_code::to_string(msg.fields.sale_condition_modifier.extended_hours_or_sold_code.get().value()) << '"'
       << ",sale_condition_modifier.special_sale_condition=\"" << itch_nlsplus::special_sale_condition::to_string(msg.fields.sale_condition_modifier.special_sale_condition.get().value()) << '"'
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const next_shares_trade_report_message& msg) {
    os << "originating_market_center_identifier=\"" << itch_nlsplus::originating_market_center_identifier::to_string(msg.fields.originating_market_center_identifier.get().value()) << '"'
       << ",next_shares_symbol=\"" << msg.fields.next_shares_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",trade_control_number=\"" << msg.fields.trade_control_number.get_trimmed().value() << '"'
       << ",proxy_price=" << msg.fields.proxy_price.get().value()
       << ",trade_size=" << msg.fields.trade_size.get().value()
       << ",nav_offset_amount=" << msg.fields.nav_offset_amount.get().value()
       << ",sale_condition_modifier.settlement_type=\"" << itch_nlsplus::settlement_type::to_string(msg.fields.sale_condition_modifier.settlement_type.get().value()) << '"'
       << ",sale_condition_modifier.trade_through_exemption=\"" << itch_nlsplus::trade_through_exemption::to_string(msg.fields.sale_condition_modifier.trade_through_exemption.get().value()) << '"'
       << ",sale_condition_modifier.extended_hours_or_sold_code=\"" << itch_nlsplus::extended_hours_or_sold_code::to_string(msg.fields.sale_condition_modifier.extended_hours_or_sold_code.get().value()) << '"'
       << ",sale_condition_modifier.special_sale_condition=\"" << itch_nlsplus::special_sale_condition::to_string(msg.fields.sale_condition_modifier.special_sale_condition.get().value()) << '"'
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancel_error_message& msg) {
    os << "originating_market_center_identifier=\"" << itch_nlsplus::originating_market_center_identifier::to_string(msg.fields.originating_market_center_identifier.get().value()) << '"'
       << ",issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",original_trade_control_number=\"" << msg.fields.original_trade_control_number.get_trimmed().value() << '"'
       << ",original_trade_price=" << msg.fields.original_trade_price.get().value()
       << ",original_trade_size=" << msg.fields.original_trade_size.get().value()
       << ",original_sale_condition_modifier.original_settlement_type=\"" << itch_nlsplus::original_settlement_type::to_string(msg.fields.original_sale_condition_modifier.original_settlement_type.get().value()) << '"'
       << ",original_sale_condition_modifier.original_trade_through_exemption=\"" << itch_nlsplus::original_trade_through_exemption::to_string(msg.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()) << '"'
       << ",original_sale_condition_modifier.original_extended_hours_or_sold_code=\"" << itch_nlsplus::original_extended_hours_or_sold_code::to_string(msg.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()) << '"'
       << ",original_sale_condition_modifier.original_special_sale_condition=\"" << itch_nlsplus::original_special_sale_condition::to_string(msg.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()) << '"'
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_form_trade_cancel_error_message& msg) {
    os << "originating_market_center_identifier=\"" << itch_nlsplus::originating_market_center_identifier::to_string(msg.fields.originating_market_center_identifier.get().value()) << '"'
       << ",issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",original_trade_control_number=\"" << msg.fields.original_trade_control_number.get_trimmed().value() << '"'
       << ",original_trade_price_long=" << msg.fields.original_trade_price_long.get().value()
       << ",original_trade_size=" << msg.fields.original_trade_size.get().value()
       << ",original_sale_condition_modifier.original_settlement_type=\"" << itch_nlsplus::original_settlement_type::to_string(msg.fields.original_sale_condition_modifier.original_settlement_type.get().value()) << '"'
       << ",original_sale_condition_modifier.original_trade_through_exemption=\"" << itch_nlsplus::original_trade_through_exemption::to_string(msg.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()) << '"'
       << ",original_sale_condition_modifier.original_extended_hours_or_sold_code=\"" << itch_nlsplus::original_extended_hours_or_sold_code::to_string(msg.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()) << '"'
       << ",original_sale_condition_modifier.original_special_sale_condition=\"" << itch_nlsplus::original_special_sale_condition::to_string(msg.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()) << '"'
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const next_shares_trade_cancel_error_message& msg) {
    os << "market_center=\"" << itch_nlsplus::market_center::to_string(msg.fields.market_center.get().value()) << '"'
       << ",issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",original_trade_control_number=\"" << msg.fields.original_trade_control_number.get_trimmed().value() << '"'
       << ",original_proxy_price=" << msg.fields.original_proxy_price.get().value()
       << ",original_nav_offset_amount=" << msg.fields.original_nav_offset_amount.get().value()
       << ",original_trade_size=" << msg.fields.original_trade_size.get().value()
       << ",original_sale_condition_modifier.original_settlement_type=\"" << itch_nlsplus::original_settlement_type::to_string(msg.fields.original_sale_condition_modifier.original_settlement_type.get().value()) << '"'
       << ",original_sale_condition_modifier.original_trade_through_exemption=\"" << itch_nlsplus::original_trade_through_exemption::to_string(msg.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()) << '"'
       << ",original_sale_condition_modifier.original_extended_hours_or_sold_code=\"" << itch_nlsplus::original_extended_hours_or_sold_code::to_string(msg.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()) << '"'
       << ",original_sale_condition_modifier.original_special_sale_condition=\"" << itch_nlsplus::original_special_sale_condition::to_string(msg.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()) << '"'
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_correction_message& msg) {
    os << "originating_market_center_identifier=\"" << itch_nlsplus::originating_market_center_identifier::to_string(msg.fields.originating_market_center_identifier.get().value()) << '"'
       << ",issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",original_trade_control_number=\"" << msg.fields.original_trade_control_number.get_trimmed().value() << '"'
       << ",original_trade_price=" << msg.fields.original_trade_price.get().value()
       << ",original_trade_size=" << msg.fields.original_trade_size.get().value()
       << ",original_sale_condition_modifier.original_settlement_type=\"" << itch_nlsplus::original_settlement_type::to_string(msg.fields.original_sale_condition_modifier.original_settlement_type.get().value()) << '"'
       << ",original_sale_condition_modifier.original_trade_through_exemption=\"" << itch_nlsplus::original_trade_through_exemption::to_string(msg.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()) << '"'
       << ",original_sale_condition_modifier.original_extended_hours_or_sold_code=\"" << itch_nlsplus::original_extended_hours_or_sold_code::to_string(msg.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()) << '"'
       << ",original_sale_condition_modifier.original_special_sale_condition=\"" << itch_nlsplus::original_special_sale_condition::to_string(msg.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()) << '"'
       << ",corrected_trade_control_number=\"" << msg.fields.corrected_trade_control_number.get_trimmed().value() << '"'
       << ",corrected_trade_price=" << msg.fields.corrected_trade_price.get().value()
       << ",corrected_trade_size=" << msg.fields.corrected_trade_size.get().value()
       << ",corrected_sale_condition_modifier.corrected_settlement_type=\"" << itch_nlsplus::corrected_settlement_type::to_string(msg.fields.corrected_sale_condition_modifier.corrected_settlement_type.get().value()) << '"'
       << ",corrected_sale_condition_modifier.corrected_trade_through_exemption=\"" << itch_nlsplus::corrected_trade_through_exemption::to_string(msg.fields.corrected_sale_condition_modifier.corrected_trade_through_exemption.get().value()) << '"'
       << ",corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code=\"" << itch_nlsplus::corrected_extended_hours_or_sold_code::to_string(msg.fields.corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get().value()) << '"'
       << ",corrected_sale_condition_modifier.corrected_special_sale_condition=\"" << itch_nlsplus::corrected_special_sale_condition::to_string(msg.fields.corrected_sale_condition_modifier.corrected_special_sale_condition.get().value()) << '"'
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_form_trade_correction_message& msg) {
    os << "originating_market_center_identifier=\"" << itch_nlsplus::originating_market_center_identifier::to_string(msg.fields.originating_market_center_identifier.get().value()) << '"'
       << ",issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",original_trade_control_number=\"" << msg.fields.original_trade_control_number.get_trimmed().value() << '"'
       << ",original_trade_price_long=" << msg.fields.original_trade_price_long.get().value()
       << ",original_trade_size=" << msg.fields.original_trade_size.get().value()
       << ",original_sale_condition_modifier.original_settlement_type=\"" << itch_nlsplus::original_settlement_type::to_string(msg.fields.original_sale_condition_modifier.original_settlement_type.get().value()) << '"'
       << ",original_sale_condition_modifier.original_trade_through_exemption=\"" << itch_nlsplus::original_trade_through_exemption::to_string(msg.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()) << '"'
       << ",original_sale_condition_modifier.original_extended_hours_or_sold_code=\"" << itch_nlsplus::original_extended_hours_or_sold_code::to_string(msg.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()) << '"'
       << ",original_sale_condition_modifier.original_special_sale_condition=\"" << itch_nlsplus::original_special_sale_condition::to_string(msg.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()) << '"'
       << ",corrected_trade_control_number=\"" << msg.fields.corrected_trade_control_number.get_trimmed().value() << '"'
       << ",corrected_trade_price_long=" << msg.fields.corrected_trade_price_long.get().value()
       << ",corrected_trade_size=" << msg.fields.corrected_trade_size.get().value()
       << ",corrected_sale_condition_modifier.corrected_settlement_type=\"" << itch_nlsplus::corrected_settlement_type::to_string(msg.fields.corrected_sale_condition_modifier.corrected_settlement_type.get().value()) << '"'
       << ",corrected_sale_condition_modifier.corrected_trade_through_exemption=\"" << itch_nlsplus::corrected_trade_through_exemption::to_string(msg.fields.corrected_sale_condition_modifier.corrected_trade_through_exemption.get().value()) << '"'
       << ",corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code=\"" << itch_nlsplus::corrected_extended_hours_or_sold_code::to_string(msg.fields.corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get().value()) << '"'
       << ",corrected_sale_condition_modifier.corrected_special_sale_condition=\"" << itch_nlsplus::corrected_special_sale_condition::to_string(msg.fields.corrected_sale_condition_modifier.corrected_special_sale_condition.get().value()) << '"'
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const next_shares_trade_correction_message& msg) {
    os << "market_center=\"" << itch_nlsplus::market_center::to_string(msg.fields.market_center.get().value()) << '"'
       << ",issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",original_trade_control_number=\"" << msg.fields.original_trade_control_number.get_trimmed().value() << '"'
       << ",original_proxy_price=" << msg.fields.original_proxy_price.get().value()
       << ",original_nav_offset_amount=" << msg.fields.original_nav_offset_amount.get().value()
       << ",original_trade_size=" << msg.fields.original_trade_size.get().value()
       << ",original_sale_condition_modifier.original_settlement_type=\"" << itch_nlsplus::original_settlement_type::to_string(msg.fields.original_sale_condition_modifier.original_settlement_type.get().value()) << '"'
       << ",original_sale_condition_modifier.original_trade_through_exemption=\"" << itch_nlsplus::original_trade_through_exemption::to_string(msg.fields.original_sale_condition_modifier.original_trade_through_exemption.get().value()) << '"'
       << ",original_sale_condition_modifier.original_extended_hours_or_sold_code=\"" << itch_nlsplus::original_extended_hours_or_sold_code::to_string(msg.fields.original_sale_condition_modifier.original_extended_hours_or_sold_code.get().value()) << '"'
       << ",original_sale_condition_modifier.original_special_sale_condition=\"" << itch_nlsplus::original_special_sale_condition::to_string(msg.fields.original_sale_condition_modifier.original_special_sale_condition.get().value()) << '"'
       << ",corrected_trade_control_number=\"" << msg.fields.corrected_trade_control_number.get_trimmed().value() << '"'
       << ",corrected_proxy_price=" << msg.fields.corrected_proxy_price.get().value()
       << ",corrected_nav_offset_amount=" << msg.fields.corrected_nav_offset_amount.get().value()
       << ",corrected_trade_size=" << msg.fields.corrected_trade_size.get().value()
       << ",corrected_sale_condition_modifier.corrected_settlement_type=\"" << itch_nlsplus::corrected_settlement_type::to_string(msg.fields.corrected_sale_condition_modifier.corrected_settlement_type.get().value()) << '"'
       << ",corrected_sale_condition_modifier.corrected_trade_through_exemption=\"" << itch_nlsplus::corrected_trade_through_exemption::to_string(msg.fields.corrected_sale_condition_modifier.corrected_trade_through_exemption.get().value()) << '"'
       << ",corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code=\"" << itch_nlsplus::corrected_extended_hours_or_sold_code::to_string(msg.fields.corrected_sale_condition_modifier.corrected_extended_hours_or_sold_code.get().value()) << '"'
       << ",corrected_sale_condition_modifier.corrected_special_sale_condition=\"" << itch_nlsplus::corrected_special_sale_condition::to_string(msg.fields.corrected_sale_condition_modifier.corrected_special_sale_condition.get().value()) << '"'
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stock_trading_action_message& msg) {
    os << "issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",current_trading_state=\"" << itch_nlsplus::current_trading_state::to_string(msg.fields.current_trading_state.get().value()) << '"'
       << ",reason=\"" << msg.fields.reason.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stock_directory_message& msg) {
    os << "stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",market_category=\"" << itch_nlsplus::market_category::to_string(msg.fields.market_category.get().value()) << '"'
       << ",financial_status_indicator=\"" << itch_nlsplus::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",round_lot_size=" << msg.fields.round_lot_size.get().value()
       << ",round_lots_only=\"" << itch_nlsplus::round_lots_only::to_string(msg.fields.round_lots_only.get().value()) << '"'
       << ",issue_classification=\"" << itch_nlsplus::issue_classification::to_string(msg.fields.issue_classification.get().value()) << '"'
       << ",issue_sub_type=\"" << msg.fields.issue_sub_type.get_trimmed().value() << '"'
       << ",authenticity=\"" << itch_nlsplus::authenticity::to_string(msg.fields.authenticity.get().value()) << '"'
       << ",short_sale_threshold_indicator=\"" << itch_nlsplus::short_sale_threshold_indicator::to_string(msg.fields.short_sale_threshold_indicator.get().value()) << '"'
       << ",ipo_flag=\"" << itch_nlsplus::ipo_flag::to_string(msg.fields.ipo_flag.get().value()) << '"'
       << ",luld_reference_price_tier=\"" << itch_nlsplus::luld_reference_price_tier::to_string(msg.fields.luld_reference_price_tier.get().value()) << '"'
       << ",etp_flag=\"" << itch_nlsplus::etp_flag::to_string(msg.fields.etp_flag.get().value()) << '"'
       << ",etp_leverage_factor=" << msg.fields.etp_leverage_factor.get().value()
       << ",inverse_indicator=\"" << itch_nlsplus::inverse_indicator::to_string(msg.fields.inverse_indicator.get().value()) << '"'
       << ",bloomberg_id=\"" << msg.fields.bloomberg_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reg_sho_short_sale_price_test_restricted_indicator_message& msg) {
    os << "issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",reg_sho_action=\"" << itch_nlsplus::reg_sho_action::to_string(msg.fields.reg_sho_action.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const adjusted_closing_price_message& msg) {
    os << "issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",adjusted_closing_price=" << msg.fields.adjusted_closing_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_form_adjusted_closing_price_message& msg) {
    os << "issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",adjusted_closing_price_long=" << msg.fields.adjusted_closing_price_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_day_trade_summary_message& msg) {
    os << "issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",market_category=\"" << itch_nlsplus::market_category::to_string(msg.fields.market_category.get().value()) << '"'
       << ",consolidated_high_price=" << msg.fields.consolidated_high_price.get().value()
       << ",consolidated_low_price=" << msg.fields.consolidated_low_price.get().value()
       << ",consolidated_closing_price=" << msg.fields.consolidated_closing_price.get().value()
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       << ",consolidated_open_price=" << msg.fields.consolidated_open_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const long_form_end_of_day_trade_summary_message& msg) {
    os << "issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",market_category=\"" << itch_nlsplus::market_category::to_string(msg.fields.market_category.get().value()) << '"'
       << ",consolidated_high_price_long=" << msg.fields.consolidated_high_price_long.get().value()
       << ",consolidated_low_price_long=" << msg.fields.consolidated_low_price_long.get().value()
       << ",consolidated_closing_price_long=" << msg.fields.consolidated_closing_price_long.get().value()
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       << ",consolidated_open_price_long=" << msg.fields.consolidated_open_price_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const next_shares_end_of_day_trade_summary_message& msg) {
    os << "issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",market_category=\"" << itch_nlsplus::market_category::to_string(msg.fields.market_category.get().value()) << '"'
       << ",consolidated_high_price=" << msg.fields.consolidated_high_price.get().value()
       << ",nav_offset_amount_high=" << msg.fields.nav_offset_amount_high.get().value()
       << ",consolidated_low_price=" << msg.fields.consolidated_low_price.get().value()
       << ",nav_offset_amount_low=" << msg.fields.nav_offset_amount_low.get().value()
       << ",consolidated_closing_price=" << msg.fields.consolidated_closing_price.get().value()
       << ",nav_offset_amount_closing=" << msg.fields.nav_offset_amount_closing.get().value()
       << ",consolidated_volume=" << msg.fields.consolidated_volume.get().value()
       << ",consolidated_open_price=" << msg.fields.consolidated_open_price.get().value()
       << ",nav_offset_amount_open=" << msg.fields.nav_offset_amount_open.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const ipo_information_message& msg) {
    os << "issue_symbol=\"" << msg.fields.issue_symbol.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_nlsplus::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",reference_for_net_change=\"" << itch_nlsplus::reference_for_net_change::to_string(msg.fields.reference_for_net_change.get().value()) << '"'
       << ",reference_price=" << msg.fields.reference_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mwcb_decline_level_message& msg) {
    os << "level_1=" << msg.fields.level_1.get().value()
       << ",level_2=" << msg.fields.level_2.get().value()
       << ",level_3=" << msg.fields.level_3.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mwcb_status_message& msg) {
    os << "breached_level=\"" << itch_nlsplus::breached_level::to_string(msg.fields.breached_level.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const ipo_quoting_period_update_message& msg) {
    os << "stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",ipo_quotation_release_time=" << msg.fields.ipo_quotation_release_time.get().value()
       << ",ipo_quotation_release_qualifier=\"" << itch_nlsplus::ipo_quotation_release_qualifier::to_string(msg.fields.ipo_quotation_release_qualifier.get().value()) << '"'
       << ",ipo_price=" << msg.fields.ipo_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const operational_halt_message& msg) {
    os << "stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",market_code=\"" << itch_nlsplus::market_code::to_string(msg.fields.market_code.get().value()) << '"'
       << ",operational_halt_action=\"" << itch_nlsplus::operational_halt_action::to_string(msg.fields.operational_halt_action.get().value()) << '"'
       ;
    return os;
}

}
