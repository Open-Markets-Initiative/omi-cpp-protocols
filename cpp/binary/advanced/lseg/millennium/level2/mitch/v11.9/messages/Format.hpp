#pragma once

#include <ostream>
#include <string_view>

#include "TimeMessage.hpp"
#include "SystemEventMessage.hpp"
#include "SymbolDirectoryMessage.hpp"
#include "SymbolStatusMessage.hpp"
#include "AddOrderMessage.hpp"
#include "AddAttributedOrderMessage.hpp"
#include "OrderDeletedMessage.hpp"
#include "OrderModifiedMessage.hpp"
#include "OrderBookClearMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "OrderExecutedWithPriceSizeMessage.hpp"
#include "TradeMessage.hpp"
#include "AuctionTradeMessage.hpp"
#include "AuctionInfoMessage.hpp"
#include "StatisticsMessage.hpp"
#include "TopOfBookMessage.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

namespace mitch_level2 = ::lseg::millennium::level2::mitch::v11_9;

inline std::ostream& operator<<(std::ostream& os, const unit_header& value) {
    os << "length=" << value.length.get().value()
       << ",message_count=" << static_cast<unsigned>(value.message_count.get().value())
       << ",market_data_group=\"" << value.market_data_group.get().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << static_cast<unsigned>(value.message_length.get().value())
       << ",message_type=\"" << mitch_level2::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const time_message& msg) {
    os << "seconds=" << msg.fields.seconds.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",event_code=\"" << mitch_level2::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_directory_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",symbol_status=\"" << mitch_level2::symbol_status::to_string(msg.fields.symbol_status.get().value()) << '"'
       << ",isin=\"" << msg.fields.isin.get_trimmed().value() << '"'
       << ",sedol=\"" << msg.fields.sedol.get_trimmed().value() << '"'
       << ",segment=\"" << msg.fields.segment.get_trimmed().value() << '"'
       << ",underlying=\"" << msg.fields.underlying.get_trimmed().value() << '"'
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",previous_close_price=" << msg.fields.previous_close_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_status_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",trading_status=\"" << mitch_level2::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",symbol_status_flags=" << static_cast<unsigned>(msg.fields.symbol_status_flags.get().value())
       << ",reason=\"" << msg.fields.reason.get_trimmed().value() << '"'
       << ",session_change_reason=\"" << mitch_level2::session_change_reason::to_string(msg.fields.session_change_reason.get().value()) << '"'
       << ",new_end_time=\"" << msg.fields.new_end_time.get_trimmed().value() << '"'
       << ",book_type=\"" << mitch_level2::book_type::to_string(msg.fields.book_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side=\"" << mitch_level2::side::to_string(msg.fields.side.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",add_order_flags=" << static_cast<unsigned>(msg.fields.add_order_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_attributed_order_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side=\"" << mitch_level2::side::to_string(msg.fields.side.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",attribution=\"" << msg.fields.attribution.get_trimmed().value() << '"'
       << ",add_attributed_order_flags=" << static_cast<unsigned>(msg.fields.add_attributed_order_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_deleted_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",order_deleted_flags=" << static_cast<unsigned>(msg.fields.order_deleted_flags.get().value())
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_modified_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",new_quantity=" << msg.fields.new_quantity.get().value()
       << ",new_price=" << msg.fields.new_price.get().value()
       << ",order_modified_flags=" << static_cast<unsigned>(msg.fields.order_modified_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_clear_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",order_book_clear_flags=" << static_cast<unsigned>(msg.fields.order_book_clear_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",trade_match_id=" << msg.fields.trade_match_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_with_price_size_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",display_quantity=" << msg.fields.display_quantity.get().value()
       << ",trade_match_id=" << msg.fields.trade_match_id.get().value()
       << ",printable=\"" << mitch_level2::printable::to_string(msg.fields.printable.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_match_id=" << msg.fields.trade_match_id.get().value()
       << ",cross_type=\"" << mitch_level2::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",sub_book=\"" << mitch_level2::sub_book::to_string(msg.fields.sub_book.get().value()) << '"'
       << ",pt_mod_flags=" << static_cast<unsigned>(msg.fields.pt_mod_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_trade_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_match_id=" << msg.fields.trade_match_id.get().value()
       << ",auction_type=\"" << mitch_level2::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",pt_mod_flags=" << static_cast<unsigned>(msg.fields.pt_mod_flags.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const auction_info_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",paired_quantity=" << msg.fields.paired_quantity.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",auction_type=\"" << mitch_level2::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const statistics_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",statistic_type=\"" << mitch_level2::statistic_type::to_string(msg.fields.statistic_type.get().value()) << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",open_close_price_indicator=\"" << mitch_level2::open_close_price_indicator::to_string(msg.fields.open_close_price_indicator.get().value()) << '"'
       << ",statistics_reserved=" << static_cast<unsigned>(msg.fields.statistics_reserved.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const top_of_book_message& msg) {
    os << "nanosecond=" << msg.fields.nanosecond.get().value()
       << ",instrument_id=" << msg.fields.instrument_id.get().value()
       << ",buy_limit_price=" << msg.fields.buy_limit_price.get().value()
       << ",buy_limit_size=" << msg.fields.buy_limit_size.get().value()
       << ",sell_limit_price=" << msg.fields.sell_limit_price.get().value()
       << ",sell_limit_size=" << msg.fields.sell_limit_size.get().value()
       ;
    return os;
}

}
