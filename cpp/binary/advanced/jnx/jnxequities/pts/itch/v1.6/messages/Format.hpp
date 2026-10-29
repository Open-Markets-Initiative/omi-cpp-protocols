#pragma once

#include <ostream>
#include <string_view>

#include "SecondsMessage.hpp"
#include "SystemEventMessage.hpp"
#include "PriceTickSizeMessage.hpp"
#include "OrderbookDirectoryMessage.hpp"
#include "TradingStateMessage.hpp"
#include "ShortSellingPriceRestrictionStateMessage.hpp"
#include "OrderAddedWithoutAttributesMessage.hpp"
#include "OrderAddedWithAttributesMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "OrderDeletedMessage.hpp"
#include "OrderReplacedMessage.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

namespace itch_pts = ::jnx::jnxequities::pts::itch::v1_6;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "session=\"" << value.session.get_trimmed().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",message_count=" << value.message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << itch_pts::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const seconds_message& msg) {
    os << "seconds=" << msg.fields.seconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",system_event=\"" << itch_pts::system_event::to_string(msg.fields.system_event.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const price_tick_size_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",price_tick_size_table_id=" << msg.fields.price_tick_size_table_id.get().value()
       << ",price_tick_size=" << msg.fields.price_tick_size.get().value()
       << ",price_start=" << msg.fields.price_start.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const orderbook_directory_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",orderbook_id=" << msg.fields.orderbook_id.get().value()
       << ",orderbook_code=\"" << msg.fields.orderbook_code.get_trimmed().value() << '"'
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",round_lot_size=" << msg.fields.round_lot_size.get().value()
       << ",price_tick_size_table_id=" << msg.fields.price_tick_size_table_id.get().value()
       << ",price_decimals=" << msg.fields.price_decimals.get().value()
       << ",upper_price_limit=" << msg.fields.upper_price_limit.get().value()
       << ",lower_price_limit=" << msg.fields.lower_price_limit.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_state_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",orderbook_id=" << msg.fields.orderbook_id.get().value()
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",trading_state=\"" << itch_pts::trading_state::to_string(msg.fields.trading_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_selling_price_restriction_state_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",orderbook_id=" << msg.fields.orderbook_id.get().value()
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",short_selling_state=\"" << itch_pts::short_selling_state::to_string(msg.fields.short_selling_state.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_added_without_attributes_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_number=" << msg.fields.order_number.get().value()
       << ",buy_sell_indicator=\"" << itch_pts::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",orderbook_id=" << msg.fields.orderbook_id.get().value()
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_added_with_attributes_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_number=" << msg.fields.order_number.get().value()
       << ",buy_sell_indicator=\"" << itch_pts::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",orderbook_id=" << msg.fields.orderbook_id.get().value()
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",attribution=\"" << msg.fields.attribution.get_trimmed().value() << '"'
       << ",order_type=\"" << itch_pts::order_type::to_string(msg.fields.order_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_number=" << msg.fields.order_number.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_deleted_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",order_number=" << msg.fields.order_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_replaced_message& msg) {
    os << "nanoseconds=" << msg.fields.nanoseconds.get().value()
       << ",original_order_number=" << msg.fields.original_order_number.get().value()
       << ",new_order_number=" << msg.fields.new_order_number.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

}
