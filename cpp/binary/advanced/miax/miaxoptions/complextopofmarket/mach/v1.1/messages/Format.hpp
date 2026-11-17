// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/Format.hpp
#pragma once

#include <ostream>
#include <string_view>

#include "SystemTimeMessage.hpp"
#include "SeriesUpdate.hpp"
#include "ComplexStrategyDefinitionMessage.hpp"
#include "SystemStateMessage.hpp"
#include "CompactComplexTopOfMarketBidMessage.hpp"
#include "CompactComplexTopOfMarketOfferMessage.hpp"
#include "WideComplexTopOfMarketBidMessage.hpp"
#include "WideComplexTopOfMarketOfferMessage.hpp"
#include "CompactComplexDoubleSidedTopOfMarketMessage.hpp"
#include "WideComplexDoubleSidedTopOfMarketMessage.hpp"
#include "StrategyTradeMessage.hpp"
#include "UnderlyingTradingStatusMessage.hpp"
#include "../json/messages/complex_strategy_definition_message_json.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

namespace mach_complextopofmarket = ::miax::miaxoptions::complextopofmarket::mach::v1_1;

inline std::ostream& operator<<(std::ostream& os, const mach_packet_header& value) {
    os << "sequence_number=" << value.sequence_number.get().value()
       << ",packet_length=" << value.packet_length.get().value()
       << ",packet_type=\"" << mach_complextopofmarket::packet_type::to_string(value.packet_type.get().value()) << '"'
       << ",session_number=" << static_cast<unsigned>(value.session_number.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const application_message& value) {
    os << "message_type=\"" << mach_complextopofmarket::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_time_message& msg) {
    os << "seconds=" << msg.fields.seconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const series_update& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",product_id=" << msg.fields.product_id.get().value()
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",security_symbol=\"" << msg.fields.security_symbol.get_trimmed().value() << '"'
       << ",expiration_date=\"" << msg.fields.expiration_date.get_trimmed().value() << '"'
       << ",strike_price=" << msg.fields.strike_price.get().value()
       << ",call_or_put=\"" << mach_complextopofmarket::call_or_put::to_string(msg.fields.call_or_put.get().value()) << '"'
       << ",opening_time=\"" << msg.fields.opening_time.get_trimmed().value() << '"'
       << ",closing_time=\"" << msg.fields.closing_time.get_trimmed().value() << '"'
       << ",restricted_option=\"" << mach_complextopofmarket::restricted_option::to_string(msg.fields.restricted_option.get().value()) << '"'
       << ",long_term_option=\"" << mach_complextopofmarket::long_term_option::to_string(msg.fields.long_term_option.get().value()) << '"'
       << ",active_on_miax=\"" << mach_complextopofmarket::active_on_miax::to_string(msg.fields.active_on_miax.get().value()) << '"'
       << ",miax_bbo_posting_increment_indicator=\"" << mach_complextopofmarket::miax_bbo_posting_increment_indicator::to_string(msg.fields.miax_bbo_posting_increment_indicator.get().value()) << '"'
       << ",liquidity_acceptance_increment_indicator=\"" << mach_complextopofmarket::liquidity_acceptance_increment_indicator::to_string(msg.fields.liquidity_acceptance_increment_indicator.get().value()) << '"'
       << ",opening_underlying_market_code=\"" << mach_complextopofmarket::opening_underlying_market_code::to_string(msg.fields.opening_underlying_market_code.get().value()) << '"'
       << ",priority_quote_width=" << msg.fields.priority_quote_width.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_strategy_definition_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",active_on_miax=\"" << mach_complextopofmarket::active_on_miax::to_string(msg.fields.active_on_miax.get().value()) << '"'
       << ",update_reason=\"" << mach_complextopofmarket::update_reason::to_string(msg.fields.update_reason.get().value()) << '"'
       << ",number_of_legs=" << static_cast<unsigned>(msg.fields.number_of_legs.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_state_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",c_to_m_version=\"" << msg.fields.c_to_m_version.get_trimmed().value() << '"'
       << ",session_id=" << msg.fields.session_id.get().value()
       << ",system_status=\"" << mach_complextopofmarket::system_status::to_string(msg.fields.system_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const compact_complex_top_of_market_bid_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",compact_price=" << msg.fields.compact_price.get().value()
       << ",compact_size=" << msg.fields.compact_size.get().value()
       << ",top_of_market_quote_condition=\"" << mach_complextopofmarket::top_of_market_quote_condition::to_string(msg.fields.top_of_market_quote_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const compact_complex_top_of_market_offer_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",compact_price=" << msg.fields.compact_price.get().value()
       << ",compact_size=" << msg.fields.compact_size.get().value()
       << ",top_of_market_quote_condition=\"" << mach_complextopofmarket::top_of_market_quote_condition::to_string(msg.fields.top_of_market_quote_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const wide_complex_top_of_market_bid_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",wide_price=" << msg.fields.wide_price.get().value()
       << ",wide_size=" << msg.fields.wide_size.get().value()
       << ",top_of_market_quote_condition=\"" << mach_complextopofmarket::top_of_market_quote_condition::to_string(msg.fields.top_of_market_quote_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const wide_complex_top_of_market_offer_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",wide_price=" << msg.fields.wide_price.get().value()
       << ",wide_size=" << msg.fields.wide_size.get().value()
       << ",top_of_market_quote_condition=\"" << mach_complextopofmarket::top_of_market_quote_condition::to_string(msg.fields.top_of_market_quote_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const compact_complex_double_sided_top_of_market_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",compact_bid.compact_bid_price=" << msg.fields.compact_bid.compact_bid_price.get().value()
       << ",compact_bid.compact_bid_size=" << msg.fields.compact_bid.compact_bid_size.get().value()
       << ",compact_bid.bid_condition=\"" << mach_complextopofmarket::bid_condition::to_string(msg.fields.compact_bid.bid_condition.get().value()) << '"'
       << ",compact_offer.compact_offer_price=" << msg.fields.compact_offer.compact_offer_price.get().value()
       << ",compact_offer.compact_offer_size=" << msg.fields.compact_offer.compact_offer_size.get().value()
       << ",compact_offer.offer_condition=\"" << mach_complextopofmarket::offer_condition::to_string(msg.fields.compact_offer.offer_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const wide_complex_double_sided_top_of_market_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",wide_bid.wide_bid_price=" << msg.fields.wide_bid.wide_bid_price.get().value()
       << ",wide_bid.wide_bid_size=" << msg.fields.wide_bid.wide_bid_size.get().value()
       << ",wide_bid.bid_condition=\"" << mach_complextopofmarket::bid_condition::to_string(msg.fields.wide_bid.bid_condition.get().value()) << '"'
       << ",wide_offer.wide_offer_price=" << msg.fields.wide_offer.wide_offer_price.get().value()
       << ",wide_offer.wide_offer_size=" << msg.fields.wide_offer.wide_offer_size.get().value()
       << ",wide_offer.offer_condition=\"" << mach_complextopofmarket::offer_condition::to_string(msg.fields.wide_offer.offer_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const strategy_trade_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",strategy_id=" << msg.fields.strategy_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",net_price=" << msg.fields.net_price.get().value()
       << ",trade_size=" << msg.fields.trade_size.get().value()
       << ",trade_condition=\"" << mach_complextopofmarket::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const underlying_trading_status_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",underlying_symbol=\"" << msg.fields.underlying_symbol.get_trimmed().value() << '"'
       << ",trading_status=\"" << mach_complextopofmarket::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",event_reason=\"" << mach_complextopofmarket::event_reason::to_string(msg.fields.event_reason.get().value()) << '"'
       << ",expected_event_time_seconds_part=" << (msg.fields.expected_event_time_seconds_part.get().has_value() ? std::to_string(msg.fields.expected_event_time_seconds_part.get().value()) : std::string_view("null"))
       << ",expected_event_time_nano_seconds_part=" << msg.fields.expected_event_time_nano_seconds_part.get().value()
       ;
    return os;
}

}
