#pragma once

#include <ostream>
#include <string_view>

#include "SnapshotRequestMessage.hpp"
#include "ErrorResponseMessage.hpp"
#include "SnapshotStartMessage.hpp"
#include "SnapshotDataMessage.hpp"
#include "SystemEventMessage.hpp"
#include "SecurityDirectoryMessage.hpp"
#include "TradingStatusMessage.hpp"
#include "RetailLiquidityIndicatorMessage.hpp"
#include "OperationalHaltStatusMessage.hpp"
#include "ShortSalePriceTestStatusMessage.hpp"
#include "QuoteUpdateMessage.hpp"
#include "TradeReportMessage.hpp"
#include "OfficialPriceMessage.hpp"
#include "TradeBreakMessage.hpp"
#include "AuctionInformationMessage.hpp"
#include "SnapshotEndMessage.hpp"
#include "../json/messages/snapshot_data_message_json.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

namespace snap_tops = ::iex::iexequities::tops::snap::v1_6;

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << snap_tops::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_request_message& msg) {
    os << "authentication_token=\"" << msg.fields.authentication_token.get_trimmed().value() << '"'
       << ",channel_id=" << msg.fields.channel_id.get().value()
       << ",session_id=" << msg.fields.session_id.get().value()
       << ",minimum_sequence_number=" << msg.fields.minimum_sequence_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const error_response_message& msg) {
    os << "reject_reason_code=\"" << snap_tops::reject_reason_code::to_string(msg.fields.reject_reason_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_start_message& msg) {
    os << "snapshot_length=" << msg.fields.snapshot_length.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_data_message& msg) {
    os << "iex_tp_header=\"" << msg.fields.iex_tp_header.get().value() << '"'
       << ",iex_tp_message_block_length=" << msg.fields.iex_tp_message_block_length.get().value()
       << ",iex_tp_message_length=" << msg.fields.iex_tp_message_length.get().value()
       << ",iex_tp_message_type=\"" << snap_tops::iex_tp_message_type::to_string(msg.fields.iex_tp_message_type.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "system_event=\"" << snap_tops::system_event::to_string(msg.fields.system_event.get().value()) << '"'
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
       << ",luld_tier=\"" << snap_tops::luld_tier::to_string(msg.fields.luld_tier.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_status_message& msg) {
    os << "trading_status=\"" << snap_tops::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",reason=\"" << msg.fields.reason.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retail_liquidity_indicator_message& msg) {
    os << "retail_liquidity_indicator=\"" << snap_tops::retail_liquidity_indicator::to_string(msg.fields.retail_liquidity_indicator.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const operational_halt_status_message& msg) {
    os << "operational_halt_status=\"" << snap_tops::operational_halt_status::to_string(msg.fields.operational_halt_status.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_sale_price_test_status_message& msg) {
    os << "short_sale_price_test_status=\"" << snap_tops::short_sale_price_test_status::to_string(msg.fields.short_sale_price_test_status.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",detail=\"" << snap_tops::detail::to_string(msg.fields.detail.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const quote_update_message& msg) {
    os << "quote_update_flags=" << static_cast<unsigned>(msg.fields.quote_update_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",bid_size=" << msg.fields.bid_size.get().value()
       << ",bid_price=" << msg.fields.bid_price.get().value()
       << ",ask_price=" << msg.fields.ask_price.get().value()
       << ",ask_size=" << msg.fields.ask_size.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_report_message& msg) {
    os << "sale_condition_flags=" << static_cast<unsigned>(msg.fields.sale_condition_flags.get().value())
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",trade_id=" << msg.fields.trade_id.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const official_price_message& msg) {
    os << "price_type=\"" << snap_tops::price_type::to_string(msg.fields.price_type.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",official_price=" << msg.fields.official_price.get().value()
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

inline std::ostream& operator<<(std::ostream& os, const auction_information_message& msg) {
    os << "auction_type=\"" << snap_tops::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",paired_shares=" << msg.fields.paired_shares.get().value()
       << ",reference_price=" << msg.fields.reference_price.get().value()
       << ",indicative_clearing_price=" << msg.fields.indicative_clearing_price.get().value()
       << ",imbalance_shares=" << msg.fields.imbalance_shares.get().value()
       << ",imbalance_side=\"" << snap_tops::imbalance_side::to_string(msg.fields.imbalance_side.get().value()) << '"'
       << ",extension_number=\"" << msg.fields.extension_number.get().value() << '"'
       << ",scheduled_auction_time=" << msg.fields.scheduled_auction_time.get().value()
       << ",auction_book_clearing_price=" << msg.fields.auction_book_clearing_price.get().value()
       << ",collar_reference_price=" << msg.fields.collar_reference_price.get().value()
       << ",lower_auction_collar=" << msg.fields.lower_auction_collar.get().value()
       << ",upper_auction_collar=" << msg.fields.upper_auction_collar.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const snapshot_end_message& msg) {
    os << "snapshot_sequence_number=" << msg.fields.snapshot_sequence_number.get().value()
       ;
    return os;
}

}
