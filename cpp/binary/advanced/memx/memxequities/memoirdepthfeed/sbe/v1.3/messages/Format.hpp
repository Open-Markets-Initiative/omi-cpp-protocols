#pragma once

#include <ostream>
#include <string_view>

#include "InstrumentDirectoryMessage.hpp"
#include "RegShoRestrictionMessage.hpp"
#include "SecurityTradingStatusMessage.hpp"
#include "TradingSessionStatusMessage.hpp"
#include "OrderAddedMessage.hpp"
#include "OrderDeletedMessage.hpp"
#include "OrderReducedMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "TradeMessage.hpp"
#include "BrokenTradeMessage.hpp"
#include "CorrectedTradeMessage.hpp"
#include "ClearBookMessage.hpp"
#include "SnapshotCompleteMessage.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

namespace sbe_memoirdepthfeed = ::memx::memxequities::memoirdepthfeed::sbe::v1_3;

inline std::ostream& operator<<(std::ostream& os, const common_header& value) {
    os << "message_type=\"" << sbe_memoirdepthfeed::message_type::to_string(value.message_type.get().value()) << '"'
       << ",header_length=" << static_cast<unsigned>(value.header_length.get().value())
       << ",session_id=" << value.session_id.get().value()
       << ",sequence_number=" << value.sequence_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sbe_header& value) {
    os << "block_length=" << value.block_length.get().value()
       << ",template_id=\"" << sbe_memoirdepthfeed::template_id::to_string(value.template_id.get().value()) << '"'
       << ",schema_id=" << static_cast<unsigned>(value.schema_id.get().value())
       << ",version=" << value.version.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const instrument_directory_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",symbol_sfx=\"" << msg.fields.symbol_sfx.get_trimmed().value() << '"'
       << ",round_lot=" << msg.fields.round_lot.get().value()
       << ",is_test_symbol=\"" << sbe_memoirdepthfeed::is_test_symbol::to_string(msg.fields.is_test_symbol.get().value()) << '"'
       << ",mpv=" << msg.fields.mpv.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const reg_sho_restriction_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",short_sale_restriction=\"" << sbe_memoirdepthfeed::short_sale_restriction::to_string(msg.fields.short_sale_restriction.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_trading_status_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",security_trading_status=\"" << sbe_memoirdepthfeed::security_trading_status::to_string(msg.fields.security_trading_status.get().value()) << '"'
       << ",security_trading_status_reason=\"" << sbe_memoirdepthfeed::security_trading_status_reason::to_string(msg.fields.security_trading_status_reason.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_session_status_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",trading_session=\"" << sbe_memoirdepthfeed::trading_session::to_string(msg.fields.trading_session.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_added_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",side=\"" << sbe_memoirdepthfeed::side::to_string(msg.fields.side.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_deleted_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_reduced_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",order_id=" << msg.fields.order_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const broken_trade_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",original_quantity=" << msg.fields.original_quantity.get().value()
       << ",original_price=" << msg.fields.original_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const corrected_trade_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       << ",original_quantity=" << msg.fields.original_quantity.get().value()
       << ",original_price=" << msg.fields.original_price.get().value()
       << ",corrected_quantity=" << msg.fields.corrected_quantity.get().value()
       << ",corrected_price=" << msg.fields.corrected_price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const clear_book_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",security_id=" << msg.fields.security_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_complete_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",as_of_sequence_number=" << msg.fields.as_of_sequence_number.get().value()
       ;
    return os;
}

}
