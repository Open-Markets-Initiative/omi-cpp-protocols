#pragma once

#include <ostream>
#include <string_view>

#include "SystemEventMessage.hpp"
#include "SecurityDirectoryMessage.hpp"
#include "TradingStatusMessage.hpp"
#include "RetailLiquidityIndicatorMessage.hpp"
#include "OperationalHaltStatusMessage.hpp"
#include "ShortSalePriceTestStatusMessage.hpp"
#include "SecurityEventMessage.hpp"
#include "AddOrderMessage.hpp"
#include "OrderModifyMessage.hpp"
#include "OrderDeleteMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "TradeMessage.hpp"
#include "TradeBreakMessage.hpp"
#include "ClearBookMessage.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

namespace iextp_deepplus = ::iex::iexequities::deepplus::iextp::v1_04;

inline std::ostream& operator<<(std::ostream& os, const iextp_header& value) {
    os << "version=" << static_cast<unsigned>(value.version.get().value())
       << ",message_protocol_id=" << value.message_protocol_id.get().value()
       << ",channel_id=" << value.channel_id.get().value()
       << ",session_id=" << value.session_id.get().value()
       << ",payload_length=" << value.payload_length.get().value()
       << ",message_count=" << value.message_count.get().value()
       << ",stream_offset=" << value.stream_offset.get().value()
       << ",first_message_sequence_number=" << value.first_message_sequence_number.get().value()
       << ",send_time=" << value.send_time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << iextp_deepplus::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "system_event=\"" << iextp_deepplus::system_event::to_string(msg.fields.system_event.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_directory_message& msg) {
    os << "security_directory_flags=" << static_cast<unsigned>(msg.fields.security_directory_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",round_lot_size=" << msg.fields.round_lot_size.get().value()
       << ",adjusted_poc_price=" << msg.fields.adjusted_poc_price.get().value()
       << ",luld_tier=\"" << iextp_deepplus::luld_tier::to_string(msg.fields.luld_tier.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_status_message& msg) {
    os << "trading_status=\"" << iextp_deepplus::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",reason=\"" << msg.fields.reason.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retail_liquidity_indicator_message& msg) {
    os << "retail_liquidity_indicator=\"" << iextp_deepplus::retail_liquidity_indicator::to_string(msg.fields.retail_liquidity_indicator.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const operational_halt_status_message& msg) {
    os << "operational_halt_status=\"" << iextp_deepplus::operational_halt_status::to_string(msg.fields.operational_halt_status.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_sale_price_test_status_message& msg) {
    os << "short_sale_price_test_status=\"" << iextp_deepplus::short_sale_price_test_status::to_string(msg.fields.short_sale_price_test_status.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",detail=\"" << iextp_deepplus::detail::to_string(msg.fields.detail.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_event_message& msg) {
    os << "security_event=\"" << iextp_deepplus::security_event::to_string(msg.fields.security_event.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_message& msg) {
    os << "side=\"" << iextp_deepplus::side::to_string(msg.fields.side.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_modify_message& msg) {
    os << "modify_flags=" << static_cast<unsigned>(msg.fields.modify_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",order_id_reference=" << msg.fields.order_id_reference.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_delete_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",order_id_reference=" << msg.fields.order_id_reference.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "sale_condition_flags=" << static_cast<unsigned>(msg.fields.sale_condition_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",order_id_reference=" << msg.fields.order_id_reference.get().value()
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "sale_condition_flags=" << static_cast<unsigned>(msg.fields.sale_condition_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_break_message& msg) {
    os << "sale_condition_flags=" << static_cast<unsigned>(msg.fields.sale_condition_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const clear_book_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       ;
    return os;
}

}
