#pragma once

#include <ostream>
#include <string_view>

#include "MarketEventMessage.hpp"
#include "SymbolInformationMessage.hpp"
#include "SymbolStateMessage.hpp"
#include "NewOrderAddMessage.hpp"
#include "OrderPartialCancelMessage.hpp"
#include "OrderCancelAllMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "TradeMessage.hpp"
#include "TradeCancelMessage.hpp"
#include "TradeCorrectMessage.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

namespace aspen_marketdatafeed = ::cixats::cixaspen::marketdatafeed::aspen::v1_4;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "market_day_identifier=\"" << value.market_day_identifier.get_trimmed().value() << '"'
       << ",feed_identifier=\"" << aspen_marketdatafeed::feed_identifier::to_string(value.feed_identifier.get().value()) << '"'
       << ",sequence=" << value.sequence.get().value()
       << ",count=" << value.count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "length=" << value.length.get().value()
       << ",message_type=\"" << aspen_marketdatafeed::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_event_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",event=\"" << aspen_marketdatafeed::event::to_string(msg.fields.event.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_information_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",listing_market=\"" << aspen_marketdatafeed::listing_market::to_string(msg.fields.listing_market.get().value()) << '"'
       << ",board_lot_size=" << msg.fields.board_lot_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_state_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",state=\"" << aspen_marketdatafeed::state::to_string(msg.fields.state.get().value()) << '"'
       << ",info=\"" << msg.fields.info.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const new_order_add_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol_id=" << msg.fields.symbol_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side=\"" << aspen_marketdatafeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",broker=\"" << msg.fields.broker.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_partial_cancel_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity_canceled=" << msg.fields.quantity_canceled.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_cancel_all_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",side=\"" << aspen_marketdatafeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",broker=\"" << msg.fields.broker.get_trimmed().value() << '"'
       << ",contra_broker=\"" << msg.fields.contra_broker.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "symbol_id=" << msg.fields.symbol_id.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",side=\"" << aspen_marketdatafeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",shares=" << msg.fields.shares.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",broker=\"" << msg.fields.broker.get_trimmed().value() << '"'
       << ",contra_broker=\"" << msg.fields.contra_broker.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancel_message& msg) {
    os << "symbol_id=" << msg.fields.symbol_id.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",shares=" << msg.fields.shares.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",broker=\"" << msg.fields.broker.get_trimmed().value() << '"'
       << ",contra_broker=\"" << msg.fields.contra_broker.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_correct_message& msg) {
    os << "symbol_id=" << msg.fields.symbol_id.get().value()
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",execution_id=" << msg.fields.execution_id.get().value()
       << ",broker=\"" << msg.fields.broker.get_trimmed().value() << '"'
       << ",contra_broker=\"" << msg.fields.contra_broker.get_trimmed().value() << '"'
       << ",original_execution_id=" << msg.fields.original_execution_id.get().value()
       << ",original_trade_price=" << msg.fields.original_trade_price.get().value()
       << ",original_trade_quantity=" << msg.fields.original_trade_quantity.get().value()
       << ",corrected_trade_price=" << msg.fields.corrected_trade_price.get().value()
       << ",corrected_trade_quantity=" << msg.fields.corrected_trade_quantity.get().value()
       ;
    return os;
}

}
