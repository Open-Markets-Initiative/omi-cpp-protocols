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
#include "PriceLevelBuyUpdateMessage.hpp"
#include "PriceLevelSellUpdateMessage.hpp"
#include "TradeReportMessage.hpp"
#include "OfficialPriceMessage.hpp"
#include "TradeBreakMessage.hpp"
#include "AuctionInformationMessage.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

namespace iextp_deep = ::iex::iexequities::deep::iextp::v1_08;

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
       << ",message_type=\"" << iextp_deep::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "system_event=\"" << iextp_deep::system_event::to_string(msg.fields.system_event.get().value()) << '"'
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
       << ",luld_tier=\"" << iextp_deep::luld_tier::to_string(msg.fields.luld_tier.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trading_status_message& msg) {
    os << "trading_status=\"" << iextp_deep::trading_status::to_string(msg.fields.trading_status.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",reason=\"" << msg.fields.reason.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const retail_liquidity_indicator_message& msg) {
    os << "retail_liquidity_indicator=\"" << iextp_deep::retail_liquidity_indicator::to_string(msg.fields.retail_liquidity_indicator.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const operational_halt_status_message& msg) {
    os << "operational_halt_status=\"" << iextp_deep::operational_halt_status::to_string(msg.fields.operational_halt_status.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const short_sale_price_test_status_message& msg) {
    os << "short_sale_price_test_status=\"" << iextp_deep::short_sale_price_test_status::to_string(msg.fields.short_sale_price_test_status.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",detail=\"" << iextp_deep::detail::to_string(msg.fields.detail.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const security_event_message& msg) {
    os << "security_event=\"" << iextp_deep::security_event::to_string(msg.fields.security_event.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const price_level_buy_update_message& msg) {
    os << "event_flags=\"" << iextp_deep::event_flags::to_string(msg.fields.event_flags.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const price_level_sell_update_message& msg) {
    os << "event_flags=\"" << iextp_deep::event_flags::to_string(msg.fields.event_flags.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",size=" << msg.fields.size.get().value()
       << ",price=" << msg.fields.price.get().value()
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
    os << "price_type=\"" << iextp_deep::price_type::to_string(msg.fields.price_type.get().value()) << '"'
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
    os << "auction_type=\"" << iextp_deep::auction_type::to_string(msg.fields.auction_type.get().value()) << '"'
       << ",timestamp=" << msg.fields.timestamp.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",paired_shares=" << msg.fields.paired_shares.get().value()
       << ",reference_price=" << msg.fields.reference_price.get().value()
       << ",indicative_clearing_price=" << msg.fields.indicative_clearing_price.get().value()
       << ",imbalance_shares=" << msg.fields.imbalance_shares.get().value()
       << ",imbalance_side=\"" << iextp_deep::imbalance_side::to_string(msg.fields.imbalance_side.get().value()) << '"'
       << ",extension_number=\"" << msg.fields.extension_number.get().value() << '"'
       << ",scheduled_auction_time=" << msg.fields.scheduled_auction_time.get().value()
       << ",auction_book_clearing_price=" << msg.fields.auction_book_clearing_price.get().value()
       << ",collar_reference_price=" << msg.fields.collar_reference_price.get().value()
       << ",lower_auction_collar=" << msg.fields.lower_auction_collar.get().value()
       << ",upper_auction_collar=" << msg.fields.upper_auction_collar.get().value()
       ;
    return os;
}

}
