#pragma once

#include <ostream>
#include <string_view>

#include "SystemTimeMessage.hpp"
#include "SymbolUpdateMessage.hpp"
#include "SystemStateMessage.hpp"
#include "SecurityTradingStatusNotificationMessage.hpp"
#include "SymbolClearMessage.hpp"
#include "AddOrderMessage.hpp"
#include "ModifyOrderMessage.hpp"
#include "DeleteOrderMessage.hpp"
#include "OrderExecutionMessage.hpp"
#include "TradeMessage.hpp"
#include "TradeCancelMessage.hpp"
#include "RefreshRequestMessage.hpp"
#include "RefreshResponseMessage.hpp"
#include "EndOfRefreshNotificationMessage.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

namespace mach_depthofmarket = ::miax::pearlequities::depthofmarket::mach::v1_3_d;

inline std::ostream& operator<<(std::ostream& os, const esesm_packet_header& value) {
    os << "esesm_packet_length=" << value.esesm_packet_length.get().value()
       << ",esesm_packet_type=\"" << mach_depthofmarket::esesm_packet_type::to_string(value.esesm_packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const mach_message& value) {
    os << "sequence_number=" << value.sequence_number.get().value()
       << ",mach_packet_length=" << value.mach_packet_length.get().value()
       << ",mach_packet_type=\"" << mach_depthofmarket::mach_packet_type::to_string(value.mach_packet_type.get().value()) << '"'
       << ",session_number=" << static_cast<unsigned>(value.session_number.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const application_message& value) {
    os << "message_type=\"" << mach_depthofmarket::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_time_message& msg) {
    os << "seconds=" << msg.fields.seconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_update_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",ticker_symbol=\"" << msg.fields.ticker_symbol.get_trimmed().value() << '"'
       << ",test_security_indicator=\"" << mach_depthofmarket::test_security_indicator::to_string(msg.fields.test_security_indicator.get().value()) << '"'
       << ",lot_size=" << msg.fields.lot_size.get().value()
       << ",opening_time=\"" << msg.fields.opening_time.get_trimmed().value() << '"'
       << ",closing_time=\"" << msg.fields.closing_time.get_trimmed().value() << '"'
       << ",primary_market_code=\"" << mach_depthofmarket::primary_market_code::to_string(msg.fields.primary_market_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_state_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",do_m_version=\"" << msg.fields.do_m_version.get_trimmed().value() << '"'
       << ",session_id=" << static_cast<unsigned>(msg.fields.session_id.get().value())
       << ",system_status=\"" << mach_depthofmarket::system_status::to_string(msg.fields.system_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_trading_status_notification_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",trading_status=\"" << mach_depthofmarket::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",market_state=\"" << mach_depthofmarket::market_state::to_string(msg.fields.market_state.get().value()) << '"'
       << ",short_sale_restriction=\"" << mach_depthofmarket::short_sale_restriction::to_string(msg.fields.short_sale_restriction.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_clear_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_side=\"" << mach_depthofmarket::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",attributable_id=\"" << msg.fields.attributable_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",modify_order_flags=" << static_cast<unsigned>(msg.fields.modify_order_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const delete_order_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_execution_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",order_execution_flags=" << static_cast<unsigned>(msg.fields.order_execution_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",correction_number=" << static_cast<unsigned>(msg.fields.correction_number.get().value())
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",trade_flags=" << static_cast<unsigned>(msg.fields.trade_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancel_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",correction_number=" << static_cast<unsigned>(msg.fields.correction_number.get().value())
       << ",price=" << msg.fields.price.get().value()
       << ",size=" << msg.fields.size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_request_message& msg) {
    os << "refresh_message_type=\"" << mach_depthofmarket::refresh_message_type::to_string(msg.fields.refresh_message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const refresh_response_message& msg) {
    os << "sequence_number=" << msg.fields.sequence_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_refresh_notification_message& msg) {
    os << "refresh_message_type=\"" << mach_depthofmarket::refresh_message_type::to_string(msg.fields.refresh_message_type.get().value()) << '"'
       ;
    return os;
}

}
