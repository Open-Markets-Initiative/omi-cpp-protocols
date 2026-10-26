#pragma once

#include <ostream>
#include <string_view>

#include "SystemEventMessage.hpp"
#include "StockDirectoryMessage.hpp"
#include "StockTradingActionMessage.hpp"
#include "RegShoRestrictionMessage.hpp"
#include "MwcbDeclineLevelMessage.hpp"
#include "MwcbBreachMessage.hpp"
#include "OperationalHaltMessage.hpp"
#include "BboQuotationMessage.hpp"
#include "PriceImprovementMessage.hpp"
#include "IpoQuotingPeriodUpdateMessage.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

namespace itch_qbbo = ::nasdaq::nsmequities::qbbo::itch::v2_1;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "session=\"" << value.session.get_trimmed().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",message_count=" << value.message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << itch_qbbo::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",event_code=\"" << itch_qbbo::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stock_directory_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",market_category=\"" << itch_qbbo::market_category::to_string(msg.fields.market_category.get().value()) << '"'
       << ",financial_status_indicator=\"" << itch_qbbo::financial_status_indicator::to_string(msg.fields.financial_status_indicator.get().value()) << '"'
       << ",round_lot_size=" << msg.fields.round_lot_size.get().value()
       << ",round_lots_only=\"" << itch_qbbo::round_lots_only::to_string(msg.fields.round_lots_only.get().value()) << '"'
       << ",issue_classification=\"" << itch_qbbo::issue_classification::to_string(msg.fields.issue_classification.get().value()) << '"'
       << ",issue_subtype=\"" << msg.fields.issue_subtype.get_trimmed().value() << '"'
       << ",authenticity=\"" << itch_qbbo::authenticity::to_string(msg.fields.authenticity.get().value()) << '"'
       << ",short_sale_threshold_indicator=\"" << itch_qbbo::short_sale_threshold_indicator::to_string(msg.fields.short_sale_threshold_indicator.get().value()) << '"'
       << ",ipo_flag=\"" << itch_qbbo::ipo_flag::to_string(msg.fields.ipo_flag.get().value()) << '"'
       << ",luld_reference_price_tier=\"" << itch_qbbo::luld_reference_price_tier::to_string(msg.fields.luld_reference_price_tier.get().value()) << '"'
       << ",etp_flag=\"" << itch_qbbo::etp_flag::to_string(msg.fields.etp_flag.get().value()) << '"'
       << ",etp_leverage_factor=" << msg.fields.etp_leverage_factor.get().value()
       << ",inverse_indicator=\"" << itch_qbbo::inverse_indicator::to_string(msg.fields.inverse_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stock_trading_action_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_qbbo::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",current_trading_state=\"" << itch_qbbo::current_trading_state::to_string(msg.fields.current_trading_state.get().value()) << '"'
       << ",reason=\"" << msg.fields.reason.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reg_sho_restriction_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",reg_sho_action=\"" << itch_qbbo::reg_sho_action::to_string(msg.fields.reg_sho_action.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mwcb_decline_level_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",level_1=" << msg.fields.level_1.get().value()
       << ",level_2=" << msg.fields.level_2.get().value()
       << ",level_3=" << msg.fields.level_3.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mwcb_breach_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",breached_level=\"" << itch_qbbo::breached_level::to_string(msg.fields.breached_level.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const operational_halt_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",market_code=\"" << itch_qbbo::market_code::to_string(msg.fields.market_code.get().value()) << '"'
       << ",operational_halt_action=\"" << itch_qbbo::operational_halt_action::to_string(msg.fields.operational_halt_action.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const bbo_quotation_message& msg) {
    os << "tracking_number=" << msg.fields.tracking_number.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",security_class=\"" << itch_qbbo::security_class::to_string(msg.fields.security_class.get().value()) << '"'
       << ",best_bid_price=" << msg.fields.best_bid_price.get().value()
       << ",best_bid_size=" << msg.fields.best_bid_size.get().value()
       << ",best_offer_price=" << msg.fields.best_offer_price.get().value()
       << ",best_offer_size=" << msg.fields.best_offer_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const price_improvement_message& msg) {
    os << "tracking=" << msg.fields.tracking.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",interest_flag=\"" << itch_qbbo::interest_flag::to_string(msg.fields.interest_flag.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const ipo_quoting_period_update_message& msg) {
    os << "tracking=" << msg.fields.tracking.get().value()
       << ",time_stamp=" << msg.fields.time_stamp.get().value()
       << ",stock=\"" << msg.fields.stock.get_trimmed().value() << '"'
       << ",ipo_quotation_release_time=" << msg.fields.ipo_quotation_release_time.get().value()
       << ",ipo_quotation_release_qualifier=\"" << itch_qbbo::ipo_quotation_release_qualifier::to_string(msg.fields.ipo_quotation_release_qualifier.get().value()) << '"'
       << ",ipo_price=" << msg.fields.ipo_price.get().value()
       ;
    return os;
}

}
