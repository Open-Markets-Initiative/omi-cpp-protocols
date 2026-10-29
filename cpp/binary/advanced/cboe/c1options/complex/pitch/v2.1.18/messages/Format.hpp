#pragma once

#include <ostream>
#include <string_view>

#include "TimeMessage.hpp"
#include "UnitClearMessage.hpp"
#include "TransactionBegin.hpp"
#include "TransactionEndMessage.hpp"
#include "ComplexInstrumentDefinitionExpandedMessage.hpp"
#include "SymbolMappingMessage.hpp"
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
#include "AuctionNotificationMessage.hpp"
#include "AuctionCancelMessage.hpp"
#include "AuctionTradeMessage.hpp"
#include "TradingStatusMessage.hpp"
#include "AuctionUpdateMessage.hpp"
#include "AuctionSummaryMessage.hpp"
#include "EndOfSessionMessage.hpp"
#include "../json/messages/complex_instrument_definition_expanded_message_json.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

namespace pitch_complex = ::cboe::c1options::complex::pitch::v2_1_18;

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
       << ",message_type=\"" << pitch_complex::message_type::to_string(value.message_type.get().value()) << '"'
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

inline std::ostream& operator<<(std::ostream& os, const transaction_begin& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const transaction_end_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const complex_instrument_definition_expanded_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",complex_instrument_id=\"" << msg.fields.complex_instrument_id.get_trimmed().value() << '"'
       << ",complex_instrument_underlying=\"" << msg.fields.complex_instrument_underlying.get_trimmed().value() << '"'
       << ",complex_instrument_type=\"" << msg.fields.complex_instrument_type.get_trimmed().value() << '"'
       << ",leg_count=" << static_cast<unsigned>(msg.fields.leg_count.get().value())
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_mapping_message& msg) {
    os << "feed_symbol=\"" << msg.fields.feed_symbol.get_trimmed().value() << '"'
       << ",osi_symbol=\"" << msg.fields.osi_symbol.get_trimmed().value() << '"'
       << ",symbol_condition=\"" << pitch_complex::symbol_condition::to_string(msg.fields.symbol_condition.get().value()) << '"'
       << ",underlying=\"" << msg.fields.underlying.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_complex::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",complex_instrument_id=\"" << msg.fields.complex_instrument_id.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_complex::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_short=" << msg.fields.quantity_short.get().value()
       << ",complex_instrument_id=\"" << msg.fields.complex_instrument_id.get_trimmed().value() << '"'
       << ",price_short=" << msg.fields.price_short.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_expanded_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_complex::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",complex_instrument_id_8=\"" << msg.fields.complex_instrument_id_8.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",participant_id=\"" << msg.fields.participant_id.get_trimmed().value() << '"'
       << ",customer_indicator=\"" << pitch_complex::customer_indicator::to_string(msg.fields.customer_indicator.get().value()) << '"'
       << ",client_id=\"" << msg.fields.client_id.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_complex::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_at_price_size_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",remaining_quantity=" << msg.fields.remaining_quantity.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_condition=\"" << pitch_complex::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reduce_size_long_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",canceled_quantity=" << msg.fields.canceled_quantity.get().value()
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
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const modify_order_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_short=" << msg.fields.quantity_short.get().value()
       << ",price_short=" << msg.fields.price_short.get().value()
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
       << ",side_indicator=\"" << pitch_complex::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",complex_instrument_id=\"" << msg.fields.complex_instrument_id.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_complex::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_short_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side_indicator=\"" << pitch_complex::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",quantity_short=" << msg.fields.quantity_short.get().value()
       << ",complex_instrument_id=\"" << msg.fields.complex_instrument_id.get_trimmed().value() << '"'
       << ",price_short=" << msg.fields.price_short.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",trade_condition=\"" << pitch_complex::trade_condition::to_string(msg.fields.trade_condition.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_notification_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",complex_instrument_id=\"" << msg.fields.complex_instrument_id.get_trimmed().value() << '"'
       << ",auction_id=" << msg.fields.auction_id.get().value()
       << ",auction_type=\"" << pitch_complex::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",side_indicator=\"" << pitch_complex::side_indicator::to_string(msg.fields.side_indicator.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",customer_indicator=\"" << pitch_complex::customer_indicator::to_string(msg.fields.customer_indicator.get().value()) << '"'
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
       << ",price=" << msg.fields.price.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_status_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",complex_symbol_id=\"" << msg.fields.complex_symbol_id.get_trimmed().value() << '"'
       << ",trading_status=\"" << pitch_complex::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",gth_trading_status=\"" << pitch_complex::gth_trading_status::to_string(msg.fields.gth_trading_status.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_update_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",complex_instrument_id_8=\"" << msg.fields.complex_instrument_id_8.get_trimmed().value() << '"'
       << ",auction_opening_type=\"" << pitch_complex::auction_opening_type::to_string(msg.fields.auction_opening_type.get().value()) << '"'
       << ",reference_price=" << msg.fields.reference_price.get().value()
       << ",buy_contracts=" << msg.fields.buy_contracts.get().value()
       << ",sell_contracts=" << msg.fields.sell_contracts.get().value()
       << ",indicative_price=" << msg.fields.indicative_price.get().value()
       << ",auction_only_price=" << msg.fields.auction_only_price.get().value()
       << ",opening_condition=\"" << msg.fields.opening_condition.get().value() << '"'
       << ",composite_market_bid_price=" << msg.fields.composite_market_bid_price.get().value()
       << ",composite_market_offer_price=" << msg.fields.composite_market_offer_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_summary_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       << ",complex_instrument_id_8=\"" << msg.fields.complex_instrument_id_8.get_trimmed().value() << '"'
       << ",auction_opening_type=\"" << pitch_complex::auction_opening_type::to_string(msg.fields.auction_opening_type.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const end_of_session_message& msg) {
    os << "time_offset=" << msg.fields.time_offset.get().value()
       ;
    return os;
}

}
