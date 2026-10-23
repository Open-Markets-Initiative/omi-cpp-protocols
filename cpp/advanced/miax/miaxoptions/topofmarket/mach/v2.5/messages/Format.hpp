#pragma once

#include <ostream>
#include <string_view>

#include "SystemTimeMessage.hpp"
#include "SimpleSeriesUpdateMessage.hpp"
#include "SystemStateMessage.hpp"
#include "SimpleTopOfMarketBestBidOrOfferCompactBidMessage.hpp"
#include "SimpleTopOfMarketBestBidOrOfferCompactOfferMessage.hpp"
#include "SimpleTopOfMarketBestBidOrOfferWideBidMessage.hpp"
#include "SimpleTopOfMarketBestBidOrOfferWideOfferMessage.hpp"
#include "SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage.hpp"
#include "SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage.hpp"
#include "LastSaleMessage.hpp"
#include "TradeCancelMessage.hpp"
#include "UnderlyingTradingStatusNotificationMessage.hpp"
#include "RefreshRequestMessage.hpp"
#include "RefreshResponseMessage.hpp"
#include "EndOfRefreshNotificationMessage.hpp"
#include "../json/messages/refresh_response_message_json.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

namespace mach_topofmarket = ::miax::miaxoptions::topofmarket::mach::v2_5;

inline std::ostream& operator<<(std::ostream& os, const sesm_packet_header& value) {
    os << "sesm_packet_length=" << value.sesm_packet_length.get().value()
       << ",sesm_packet_type=\"" << mach_topofmarket::sesm_packet_type::to_string(value.sesm_packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mach_message& value) {
    os << "sequence_number=" << value.sequence_number.get().value()
       << ",packet_length=" << value.packet_length.get().value()
       << ",packet_type=\"" << mach_topofmarket::packet_type::to_string(value.packet_type.get().value()) << '"'
       << ",session_number=" << static_cast<unsigned>(value.session_number.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const application_message& value) {
    os << "message_type=\"" << mach_topofmarket::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_time_message& msg) {
    os << "seconds=" << msg.fields.seconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_series_update_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",expiration_date=\"" << msg.fields.expiration_date.get_trimmed().value() << '"'
       << ",strike_price=" << msg.fields.strike_price.get().value()
       << ",call_or_put=\"" << mach_topofmarket::call_or_put::to_string(msg.fields.call_or_put.get().value()) << '"'
       << ",opening_time=\"" << msg.fields.opening_time.get_trimmed().value() << '"'
       << ",closing_time=\"" << msg.fields.closing_time.get_trimmed().value() << '"'
       << ",restricted_option=\"" << mach_topofmarket::restricted_option::to_string(msg.fields.restricted_option.get().value()) << '"'
       << ",long_term_option=\"" << mach_topofmarket::long_term_option::to_string(msg.fields.long_term_option.get().value()) << '"'
       << ",active_on_miax=\"" << mach_topofmarket::active_on_miax::to_string(msg.fields.active_on_miax.get().value()) << '"'
       << ",miax_bbo_posting_increment_indicator=\"" << mach_topofmarket::miax_bbo_posting_increment_indicator::to_string(msg.fields.miax_bbo_posting_increment_indicator.get().value()) << '"'
       << ",liquidity_acceptance_increment_indicator=\"" << mach_topofmarket::liquidity_acceptance_increment_indicator::to_string(msg.fields.liquidity_acceptance_increment_indicator.get().value()) << '"'
       << ",opening_underlying_market_code=\"" << mach_topofmarket::opening_underlying_market_code::to_string(msg.fields.opening_underlying_market_code.get().value()) << '"'
       << ",priority_quote_width=" << msg.fields.priority_quote_width.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_state_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",to_m_version=\"" << msg.fields.to_m_version.get_trimmed().value() << '"'
       << ",session_id=" << msg.fields.session_id.get().value()
       << ",system_status=\"" << mach_topofmarket::system_status::to_string(msg.fields.system_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_top_of_market_best_bid_or_offer_compact_bid_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",mbbo_price_short=" << msg.fields.mbbo_price_short.get().value()
       << ",mbbo_size_short=" << msg.fields.mbbo_size_short.get().value()
       << ",mbbo_priority_customer_size_short=" << msg.fields.mbbo_priority_customer_size_short.get().value()
       << ",mbbo_condition=\"" << mach_topofmarket::mbbo_condition::to_string(msg.fields.mbbo_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_top_of_market_best_bid_or_offer_compact_offer_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",mbbo_price_short=" << msg.fields.mbbo_price_short.get().value()
       << ",mbbo_size_short=" << msg.fields.mbbo_size_short.get().value()
       << ",mbbo_priority_customer_size_short=" << msg.fields.mbbo_priority_customer_size_short.get().value()
       << ",mbbo_condition=\"" << mach_topofmarket::mbbo_condition::to_string(msg.fields.mbbo_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_top_of_market_best_bid_or_offer_wide_bid_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",mbbo_price_long=" << msg.fields.mbbo_price_long.get().value()
       << ",mbbo_size_long=" << msg.fields.mbbo_size_long.get().value()
       << ",mbbo_priority_customer_size_long=" << msg.fields.mbbo_priority_customer_size_long.get().value()
       << ",mbbo_condition=\"" << mach_topofmarket::mbbo_condition::to_string(msg.fields.mbbo_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_top_of_market_best_bid_or_offer_wide_offer_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",mbbo_price_long=" << msg.fields.mbbo_price_long.get().value()
       << ",mbbo_size_long=" << msg.fields.mbbo_size_long.get().value()
       << ",mbbo_priority_customer_size_long=" << msg.fields.mbbo_priority_customer_size_long.get().value()
       << ",mbbo_condition=\"" << mach_topofmarket::mbbo_condition::to_string(msg.fields.mbbo_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_double_sided_top_of_market_best_bid_or_offer_compact_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",bid_price_short=" << msg.fields.bid_price_short.get().value()
       << ",bid_size_short=" << msg.fields.bid_size_short.get().value()
       << ",bid_priority_customer_size_short=" << msg.fields.bid_priority_customer_size_short.get().value()
       << ",bid_condition=\"" << mach_topofmarket::bid_condition::to_string(msg.fields.bid_condition.get().value()) << '"'
       << ",offer_price_short=" << msg.fields.offer_price_short.get().value()
       << ",offer_size_short=" << msg.fields.offer_size_short.get().value()
       << ",offer_priority_customer_size_short=" << msg.fields.offer_priority_customer_size_short.get().value()
       << ",offer_condition=\"" << mach_topofmarket::offer_condition::to_string(msg.fields.offer_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const simple_double_sided_top_of_market_best_bid_or_offer_wide_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",bid_price_long=" << msg.fields.bid_price_long.get().value()
       << ",bid_size_long=" << msg.fields.bid_size_long.get().value()
       << ",bid_priority_customer_size_long=" << msg.fields.bid_priority_customer_size_long.get().value()
       << ",bid_condition=\"" << mach_topofmarket::bid_condition::to_string(msg.fields.bid_condition.get().value()) << '"'
       << ",offer_price_long=" << msg.fields.offer_price_long.get().value()
       << ",offer_size_long=" << msg.fields.offer_size_long.get().value()
       << ",offer_priority_customer_size_long=" << msg.fields.offer_priority_customer_size_long.get().value()
       << ",offer_condition=\"" << mach_topofmarket::offer_condition::to_string(msg.fields.offer_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const last_sale_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",correction_number=" << static_cast<unsigned>(msg.fields.correction_number.get().value())
       << ",reference_trade_id=" << msg.fields.reference_trade_id.get().value()
       << ",reference_correction_number=" << static_cast<unsigned>(msg.fields.reference_correction_number.get().value())
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",trade_size=" << msg.fields.trade_size.get().value()
       << ",trade_condition=\"" << mach_topofmarket::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancel_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",correction_number=" << static_cast<unsigned>(msg.fields.correction_number.get().value())
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",trade_size=" << msg.fields.trade_size.get().value()
       << ",trade_condition=\"" << mach_topofmarket::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const underlying_trading_status_notification_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",trading_status=\"" << mach_topofmarket::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",event_reason=\"" << mach_topofmarket::event_reason::to_string(msg.fields.event_reason.get().value()) << '"'
       << ",expected_event_time_seconds_part=" << msg.fields.expected_event_time_seconds_part.get().value()
       << ",expected_event_time_nano_seconds_part=" << msg.fields.expected_event_time_nano_seconds_part.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_request_message& msg) {
    os << "refresh_message_type=\"" << mach_topofmarket::refresh_message_type::to_string(msg.fields.refresh_message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_response_message& msg) {
    os << "sequence_number=" << msg.fields.sequence_number.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_refresh_notification_message& msg) {
    os << "refresh_message_type=\"" << mach_topofmarket::refresh_message_type::to_string(msg.fields.refresh_message_type.get().value()) << '"'
       ;
    return os;
}

}
