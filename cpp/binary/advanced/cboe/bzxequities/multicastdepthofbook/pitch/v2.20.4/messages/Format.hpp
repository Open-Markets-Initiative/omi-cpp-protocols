#pragma once

#include <ostream>
#include <string_view>

#include "TimeMessage.hpp"
#include "UnitClearMessage.hpp"
#include "AddOrderLongMessage.hpp"
#include "AddOrderShortMessage.hpp"
#include "AddOrderExpandedMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "OrderExecutedAtPriceSizeMessage.hpp"
#include "ReduceSizeLongMessage.hpp"
#include "ReduceSizeShortMessage.hpp"
#include "ModifyOrderLongMessage.hpp"
#include "ModifyOrderShortMessage.hpp"
#include "DeleteOrderMessage.hpp"
#include "TradeLongMessage.hpp"
#include "TradeShortMessage.hpp"
#include "TradeExpandedMessage.hpp"
#include "TradeBreakMessage.hpp"
#include "EndOfSessionMessage.hpp"
#include "SymbolMappingMessage.hpp"
#include "TradingStatusMessage.hpp"
#include "AuctionUpdateMessage.hpp"
#include "AuctionSummaryMessage.hpp"
#include "RetailPriceImprovementMessage.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

namespace pitch_multicastdepthofbook = ::cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "length=" << value.length.get().value()
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",unit=" << static_cast<unsigned>(value.unit.get().value())
       << ",sequence=" << value.sequence.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << static_cast<unsigned>(value.message_length.get().value())
       << ",message_type=\"" << pitch_multicastdepthofbook::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const time_message& msg) {
    os << "time=" << msg.fields.time.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const unit_clear_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_binary_4=" << msg.fields.quantity_binary_4.get().value()
       << ",symbol_short=\"" << msg.fields.symbol_short.get_trimmed().value() << '"'
       << ",price_binary_long_price_8=" << msg.fields.price_binary_long_price_8.get().value()
       << ",add_flags=" << static_cast<unsigned>(msg.fields.add_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_binary_2=" << msg.fields.quantity_binary_2.get().value()
       << ",symbol_short=\"" << msg.fields.symbol_short.get_trimmed().value() << '"'
       << ",price_binary_short_price_2=" << msg.fields.price_binary_short_price_2.get().value()
       << ",add_flags=" << static_cast<unsigned>(msg.fields.add_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_expanded_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_binary_4=" << msg.fields.quantity_binary_4.get().value()
       << ",symbol_long=\"" << msg.fields.symbol_long.get_trimmed().value() << '"'
       << ",price_binary_long_price_8=" << msg.fields.price_binary_long_price_8.get().value()
       << ",add_flags=" << static_cast<unsigned>(msg.fields.add_flags.get().value())
       << ",participant_id=\"" << msg.fields.participant_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_at_price_size_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",remaining_quantity=" << msg.fields.remaining_quantity.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",price_binary_long_price_8=" << msg.fields.price_binary_long_price_8.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reduce_size_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",canceled_quantity_binary_4=" << msg.fields.canceled_quantity_binary_4.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reduce_size_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",canceled_quantity_binary_2=" << msg.fields.canceled_quantity_binary_2.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_binary_4=" << msg.fields.quantity_binary_4.get().value()
       << ",price_binary_long_price_8=" << msg.fields.price_binary_long_price_8.get().value()
       << ",modify_flags=" << static_cast<unsigned>(msg.fields.modify_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_binary_2=" << msg.fields.quantity_binary_2.get().value()
       << ",price_binary_short_price_2=" << msg.fields.price_binary_short_price_2.get().value()
       << ",modify_flags=" << static_cast<unsigned>(msg.fields.modify_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const delete_order_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_binary_4=" << msg.fields.quantity_binary_4.get().value()
       << ",symbol_short=\"" << msg.fields.symbol_short.get_trimmed().value() << '"'
       << ",price_binary_long_price_8=" << msg.fields.price_binary_long_price_8.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_binary_2=" << msg.fields.quantity_binary_2.get().value()
       << ",symbol_short=\"" << msg.fields.symbol_short.get_trimmed().value() << '"'
       << ",price_binary_short_price_2=" << msg.fields.price_binary_short_price_2.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_expanded_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_binary_4=" << msg.fields.quantity_binary_4.get().value()
       << ",symbol_long=\"" << msg.fields.symbol_long.get_trimmed().value() << '"'
       << ",price_binary_long_price_8=" << msg.fields.price_binary_long_price_8.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_break_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_session_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_mapping_message& msg) {
    os << "feed_symbol=\"" << msg.fields.feed_symbol.get_trimmed().value() << '"'
       << ",osi_symbol=\"" << msg.fields.osi_symbol.get_trimmed().value() << '"'
       << ",symbol_condition=\"" << pitch_multicastdepthofbook::symbol_condition::to_string(msg.fields.symbol_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_status_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol_long=\"" << msg.fields.symbol_long.get_trimmed().value() << '"'
       << ",trading_status=\"" << pitch_multicastdepthofbook::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",reg_sho_action=\"" << pitch_multicastdepthofbook::reg_sho_action::to_string(msg.fields.reg_sho_action.get().value()) << '"'
       << ",second_reserved_1=\"" << msg.fields.second_reserved_1.get().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_update_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",stock_symbol=\"" << msg.fields.stock_symbol.get_trimmed().value() << '"'
       << ",auction_type=\"" << pitch_multicastdepthofbook::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",reference_price=" << msg.fields.reference_price.get().value()
       << ",buy_shares=" << msg.fields.buy_shares.get().value()
       << ",sell_shares=" << msg.fields.sell_shares.get().value()
       << ",indicative_price=" << msg.fields.indicative_price.get().value()
       << ",auction_only_price=" << msg.fields.auction_only_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_summary_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",stock_symbol=\"" << msg.fields.stock_symbol.get_trimmed().value() << '"'
       << ",auction_type=\"" << pitch_multicastdepthofbook::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",price_binary_8=" << msg.fields.price_binary_8.get().value()
       << ",shares=" << msg.fields.shares.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retail_price_improvement_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol_long=\"" << msg.fields.symbol_long.get_trimmed().value() << '"'
       << ",retail_price_improvement=\"" << pitch_multicastdepthofbook::retail_price_improvement::to_string(msg.fields.retail_price_improvement.get().value()) << '"'
       ;
    return os;
}

}
