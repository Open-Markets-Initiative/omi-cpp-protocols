#pragma once

#include <ostream>
#include <string_view>

#include "TimeMessage.hpp"
#include "UnitClearMessage.hpp"
#include "TransactionBeginMessage.hpp"
#include "TransactionEndMessage.hpp"
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
#include "WidthUpdateMessage.hpp"
#include "OptionsAuctionUpdateMessage.hpp"
#include "AuctionSummaryMessage.hpp"
#include "AuctionNotificationMessage.hpp"
#include "AuctionCancelMessage.hpp"
#include "AuctionTradeMessage.hpp"
#include "SoqStrikeRangeUpdateMessage.hpp"
#include "ConstituentSymbolMappingMessage.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

namespace pitch_multicastdepthofbook = ::cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80;

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

inline std::ostream& operator<<(std::ostream& os, const transaction_begin_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const transaction_end_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_long=" << msg.fields.quantity_long.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",add_flags=" << static_cast<unsigned>(msg.fields.add_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_short=" << msg.fields.quantity_short.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price_short=" << msg.fields.price_short.get().value()
       << ",add_flags=" << static_cast<unsigned>(msg.fields.add_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_expanded_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_long=" << msg.fields.quantity_long.get().value()
       << ",expanded_symbol=\"" << msg.fields.expanded_symbol.get_trimmed().value() << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",add_flags=" << static_cast<unsigned>(msg.fields.add_flags.get().value())
       << ",participant_id=\"" << msg.fields.participant_id.get_trimmed().value() << '"'
       << ",customer_indicator=\"" << pitch_multicastdepthofbook::customer_indicator::to_string(msg.fields.customer_indicator.get().value()) << '"'
       << ",client_id=\"" << msg.fields.client_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_multicastdepthofbook::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_at_price_size_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",remaining_quantity=" << msg.fields.remaining_quantity.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",trade_condition=\"" << pitch_multicastdepthofbook::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reduce_size_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",canceled_quantity_long=" << msg.fields.canceled_quantity_long.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reduce_size_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",canceled_quantity_short=" << msg.fields.canceled_quantity_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_long=" << msg.fields.quantity_long.get().value()
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",modify_flags=" << static_cast<unsigned>(msg.fields.modify_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_short=" << msg.fields.quantity_short.get().value()
       << ",price_short=" << msg.fields.price_short.get().value()
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
       << ",quantity_long=" << msg.fields.quantity_long.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_multicastdepthofbook::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_short=" << msg.fields.quantity_short.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price_short=" << msg.fields.price_short.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_multicastdepthofbook::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_expanded_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_multicastdepthofbook::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_long=" << msg.fields.quantity_long.get().value()
       << ",expanded_symbol=\"" << msg.fields.expanded_symbol.get_trimmed().value() << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_multicastdepthofbook::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
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
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_mapping_message& msg) {
    os << "feed_symbol=\"" << msg.fields.feed_symbol.get_trimmed().value() << '"'
       << ",osi_symbol=\"" << msg.fields.osi_symbol.get_trimmed().value() << '"'
       << ",symbol_condition=\"" << pitch_multicastdepthofbook::symbol_condition::to_string(msg.fields.symbol_condition.get().value()) << '"'
       << ",underlying=\"" << msg.fields.underlying.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_status_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trading_status=\"" << pitch_multicastdepthofbook::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",gth_trading_status=\"" << pitch_multicastdepthofbook::gth_trading_status::to_string(msg.fields.gth_trading_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const width_update_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",underlying=\"" << msg.fields.underlying.get_trimmed().value() << '"'
       << ",width_type=\"" << pitch_multicastdepthofbook::width_type::to_string(msg.fields.width_type.get().value()) << '"'
       << ",multiplier=" << msg.fields.multiplier.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const options_auction_update_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",expanded_symbol=\"" << msg.fields.expanded_symbol.get_trimmed().value() << '"'
       << ",auction_type=\"" << pitch_multicastdepthofbook::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",reference_price=" << msg.fields.reference_price.get().value()
       << ",buy_contracts=" << msg.fields.buy_contracts.get().value()
       << ",sell_contracts=" << msg.fields.sell_contracts.get().value()
       << ",indicative_price=" << msg.fields.indicative_price.get().value()
       << ",auction_only_price=" << msg.fields.auction_only_price.get().value()
       << ",opening_condition=\"" << pitch_multicastdepthofbook::opening_condition::to_string(msg.fields.opening_condition.get().value()) << '"'
       << ",composite_market_bid_price=" << msg.fields.composite_market_bid_price.get().value()
       << ",composite_market_offer_price=" << msg.fields.composite_market_offer_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_summary_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",stock_symbol=\"" << msg.fields.stock_symbol.get_trimmed().value() << '"'
       << ",auction_type=\"" << pitch_multicastdepthofbook::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",shares_contracts=" << msg.fields.shares_contracts.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_notification_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",auction_id=" << msg.fields.auction_id.get().value()
       << ",auction_type=\"" << pitch_multicastdepthofbook::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",side=\"" << pitch_multicastdepthofbook::side::to_string(msg.fields.side.get().value()) << '"'
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",contracts=" << msg.fields.contracts.get().value()
       << ",customer_indicator=\"" << pitch_multicastdepthofbook::customer_indicator::to_string(msg.fields.customer_indicator.get().value()) << '"'
       << ",participant_id=\"" << msg.fields.participant_id.get_trimmed().value() << '"'
       << ",auction_end_offset=" << msg.fields.auction_end_offset.get().value()
       << ",client_id=\"" << msg.fields.client_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_cancel_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",auction_id=" << msg.fields.auction_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_trade_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",auction_id=" << msg.fields.auction_id.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",price_long=" << msg.fields.price_long.get().value()
       << ",contracts=" << msg.fields.contracts.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const soq_strike_range_update_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",soq_identifier=\"" << msg.fields.soq_identifier.get_trimmed().value() << '"'
       << ",lower_strike_price=" << msg.fields.lower_strike_price.get().value()
       << ",upper_strike_price=" << msg.fields.upper_strike_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const constituent_symbol_mapping_message& msg) {
    os << "feed_symbol=\"" << msg.fields.feed_symbol.get_trimmed().value() << '"'
       << ",osi_symbol=\"" << msg.fields.osi_symbol.get_trimmed().value() << '"'
       << ",symbol_condition=\"" << pitch_multicastdepthofbook::symbol_condition::to_string(msg.fields.symbol_condition.get().value()) << '"'
       << ",underlying=\"" << msg.fields.underlying.get_trimmed().value() << '"'
       << ",soq_identifier=\"" << msg.fields.soq_identifier.get_trimmed().value() << '"'
       ;
    return os;
}

}
