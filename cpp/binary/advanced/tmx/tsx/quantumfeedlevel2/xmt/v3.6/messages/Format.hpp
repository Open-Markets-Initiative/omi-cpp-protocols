// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: messages/Format.hpp
#pragma once

#include <ostream>
#include <string_view>

#include "HeartbeatBody.hpp"
#include "SymbolStatusMessage.hpp"
#include "OrderBookMessage.hpp"
#include "OrderBookTermsMessage.hpp"
#include "AssignCopOrdersMessage.hpp"
#include "AssignCopNoOrdersMessage.hpp"
#include "AssignLimitMessage.hpp"
#include "MarketStateUpdateMessage.hpp"
#include "MocImbalanceMessage.hpp"
#include "OrderBookedMessage.hpp"
#include "OrderBookedTermsMessage.hpp"
#include "OrderCancelledMessage.hpp"
#include "OrderCancelledTermsMessage.hpp"
#include "OrderPriceTimeAssignedMessage.hpp"
#include "OrderPriceTimeAssignedTermsMessage.hpp"
#include "StockStatusMessage.hpp"
#include "TradeReportMessage.hpp"
#include "TradeReportTermsMessage.hpp"
#include "TradeCancelledMessage.hpp"
#include "TradeCancelledTermsMessage.hpp"
#include "TradeCorrectionMessage.hpp"
#include "TradeCorrectionTermsMessage.hpp"
#include "../json/messages/heartbeat_body_json.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

namespace xmt_quantumfeedlevel2 = ::tmx::tsx::quantumfeedlevel2::xmt::v3_6;

inline std::ostream& operator<<(std::ostream& os, const frame_header& value) {
    os << "start_of_frame=" << static_cast<unsigned>(value.start_of_frame.get().value())
       << ",protocol_name=\"" << value.protocol_name.get().value() << '"'
       << ",protocol_version=\"" << value.protocol_version.get().value() << '"'
       << ",message_length=" << value.message_length.get().value()
       << ",session_id=" << value.session_id.get().value()
       << ",ack_required_poss_dup=\"" << xmt_quantumfeedlevel2::ack_required_poss_dup::to_string(value.ack_required_poss_dup.get().value()) << '"'
       << ",num_body=" << static_cast<unsigned>(value.num_body.get().value())
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const body_header& value) {
    os << "msg_length=" << value.msg_length.get().value()
       << ",msg_type=\"" << xmt_quantumfeedlevel2::msg_type::to_string(value.msg_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const business_header& value) {
    os << "msg_version=" << static_cast<unsigned>(value.msg_version.get().value())
       << ",source_id=\"" << xmt_quantumfeedlevel2::source_id::to_string(value.source_id.get().value()) << '"'
       << ",stream_id=" << value.stream_id.get().value()
       << ",sequence_0=" << static_cast<unsigned>(value.sequence_0.get().value())
       << ",sequence_1=" << value.sequence_1.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const heartbeat_body& msg) {
    os << "body_header.msg_length=" << msg.fields.body_header.msg_length.get().value()
       << ",body_header.msg_type=\"" << xmt_quantumfeedlevel2::msg_type::to_string(msg.fields.body_header.msg_type.get().value()) << '"'
       << ",admin_id=" << static_cast<unsigned>(msg.fields.admin_id.get().value())
       << ",hb_interval=" << msg.fields.hb_interval.get().value()
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const symbol_status_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",stock_group=" << (msg.fields.stock_group.get().has_value() ? std::to_string(msg.fields.stock_group.get().value()) : std::string_view("null"))
       << ",cusip=\"" << msg.fields.cusip.get_trimmed().value() << '"'
       << ",board_lot=" << (msg.fields.board_lot.get().has_value() ? std::to_string(msg.fields.board_lot.get().value()) : std::string_view("null"))
       << ",currency=\"" << xmt_quantumfeedlevel2::currency::to_string(msg.fields.currency.get().value()) << '"'
       << ",face_value=" << (msg.fields.face_value.get().has_value() ? std::to_string(msg.fields.face_value.get().value()) : std::string_view("null"))
       << ",last_sale=" << (msg.fields.last_sale.get().has_value() ? std::to_string(msg.fields.last_sale.get().value()) : std::string_view("null"))
       << ",listing_market=\"" << xmt_quantumfeedlevel2::listing_market::to_string(msg.fields.listing_market.get().value()) << '"'
       << ",product_type=\"" << xmt_quantumfeedlevel2::product_type::to_string(msg.fields.product_type.get().value()) << '"'
       << ",buy_maximum_quantity=" << (msg.fields.buy_maximum_quantity.get().has_value() ? std::to_string(msg.fields.buy_maximum_quantity.get().value()) : std::string_view("null"))
       << ",buy_minimum_quantity=" << (msg.fields.buy_minimum_quantity.get().has_value() ? std::to_string(msg.fields.buy_minimum_quantity.get().value()) : std::string_view("null"))
       << ",sell_maximum_quantity=" << (msg.fields.sell_maximum_quantity.get().has_value() ? std::to_string(msg.fields.sell_maximum_quantity.get().value()) : std::string_view("null"))
       << ",sell_minimum_quantity=" << (msg.fields.sell_minimum_quantity.get().has_value() ? std::to_string(msg.fields.sell_minimum_quantity.get().value()) : std::string_view("null"))
       << ",stock_state=\"" << msg.fields.stock_state.get_trimmed().value() << '"'
       << ",test_symbol=\"" << xmt_quantumfeedlevel2::test_symbol::to_string(msg.fields.test_symbol.get().value()) << '"'
       << ",moc_eligible=\"" << xmt_quantumfeedlevel2::moc_eligible::to_string(msg.fields.moc_eligible.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",broker_number=" << (msg.fields.broker_number.get().has_value() ? std::to_string(msg.fields.broker_number.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",order_id=" << (msg.fields.order_id.get().has_value() ? std::to_string(msg.fields.order_id.get().value()) : std::string_view("null"))
       << ",order_price=" << msg.fields.order_price.get().value()
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",priority_time_stamp=" << (msg.fields.priority_time_stamp.get().has_value() ? std::to_string(msg.fields.priority_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_terms_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",broker_number=" << (msg.fields.broker_number.get().has_value() ? std::to_string(msg.fields.broker_number.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",order_id=" << (msg.fields.order_id.get().has_value() ? std::to_string(msg.fields.order_id.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",non_resident=\"" << xmt_quantumfeedlevel2::non_resident::to_string(msg.fields.non_resident.get().value()) << '"'
       << ",settlement_terms=\"" << xmt_quantumfeedlevel2::settlement_terms::to_string(msg.fields.settlement_terms.get().value()) << '"'
       << ",settlement_date=" << (msg.fields.settlement_date.get().has_value() ? std::to_string(msg.fields.settlement_date.get().value()) : std::string_view("null"))
       << ",priority_time_stamp=" << (msg.fields.priority_time_stamp.get().has_value() ? std::to_string(msg.fields.priority_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const assign_cop_orders_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",calculated_opening_price=" << (msg.fields.calculated_opening_price.get().has_value() ? std::to_string(msg.fields.calculated_opening_price.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",cop_order.broker_number=" << (msg.fields.cop_order.broker_number.get().has_value() ? std::to_string(msg.fields.cop_order.broker_number.get().value()) : std::string_view("null"))
       << ",cop_order.order_id=" << (msg.fields.cop_order.order_id.get().has_value() ? std::to_string(msg.fields.cop_order.order_id.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const assign_cop_no_orders_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",calculated_opening_price=" << (msg.fields.calculated_opening_price.get().has_value() ? std::to_string(msg.fields.calculated_opening_price.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const assign_limit_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",calculated_opening_price=" << (msg.fields.calculated_opening_price.get().has_value() ? std::to_string(msg.fields.calculated_opening_price.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",cop_limit.broker_number=" << (msg.fields.cop_limit.broker_number.get().has_value() ? std::to_string(msg.fields.cop_limit.broker_number.get().value()) : std::string_view("null"))
       << ",cop_limit.order_id=" << (msg.fields.cop_limit.order_id.get().has_value() ? std::to_string(msg.fields.cop_limit.order_id.get().value()) : std::string_view("null"))
       << ",cop_limit.price=" << (msg.fields.cop_limit.price.get().has_value() ? std::to_string(msg.fields.cop_limit.price.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const market_state_update_message& msg) {
    os << "market_state=\"" << xmt_quantumfeedlevel2::market_state::to_string(msg.fields.market_state.get().value()) << '"'
       << ",stock_group=" << (msg.fields.stock_group.get().has_value() ? std::to_string(msg.fields.stock_group.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const moc_imbalance_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",imbalance_side=\"" << xmt_quantumfeedlevel2::imbalance_side::to_string(msg.fields.imbalance_side.get().value()) << '"'
       << ",imbalance_volume=" << (msg.fields.imbalance_volume.get().has_value() ? std::to_string(msg.fields.imbalance_volume.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       << ",imbalance_reference_price=" << (msg.fields.imbalance_reference_price.get().has_value() ? std::to_string(msg.fields.imbalance_reference_price.get().value()) : std::string_view("null"))
       << ",paired_volume=" << (msg.fields.paired_volume.get().has_value() ? std::to_string(msg.fields.paired_volume.get().value()) : std::string_view("null"))
       << ",market_order_imbalance_volume=" << (msg.fields.market_order_imbalance_volume.get().has_value() ? std::to_string(msg.fields.market_order_imbalance_volume.get().value()) : std::string_view("null"))
       << ",market_order_imbalance_side=\"" << xmt_quantumfeedlevel2::market_order_imbalance_side::to_string(msg.fields.market_order_imbalance_side.get().value()) << '"'
       << ",near_indicative_closing_price=" << (msg.fields.near_indicative_closing_price.get().has_value() ? std::to_string(msg.fields.near_indicative_closing_price.get().value()) : std::string_view("null"))
       << ",far_indicative_closing_price=" << (msg.fields.far_indicative_closing_price.get().has_value() ? std::to_string(msg.fields.far_indicative_closing_price.get().value()) : std::string_view("null"))
       << ",price_variation=" << (msg.fields.price_variation.get().has_value() ? std::to_string(msg.fields.price_variation.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_booked_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",broker_number=" << (msg.fields.broker_number.get().has_value() ? std::to_string(msg.fields.broker_number.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",order_id=" << (msg.fields.order_id.get().has_value() ? std::to_string(msg.fields.order_id.get().value()) : std::string_view("null"))
       << ",order_price=" << msg.fields.order_price.get().value()
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",priority_time_stamp=" << (msg.fields.priority_time_stamp.get().has_value() ? std::to_string(msg.fields.priority_time_stamp.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_booked_terms_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",broker_number=" << (msg.fields.broker_number.get().has_value() ? std::to_string(msg.fields.broker_number.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",order_id=" << (msg.fields.order_id.get().has_value() ? std::to_string(msg.fields.order_id.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",non_resident=\"" << xmt_quantumfeedlevel2::non_resident::to_string(msg.fields.non_resident.get().value()) << '"'
       << ",settlement_terms=\"" << xmt_quantumfeedlevel2::settlement_terms::to_string(msg.fields.settlement_terms.get().value()) << '"'
       << ",settlement_date=" << (msg.fields.settlement_date.get().has_value() ? std::to_string(msg.fields.settlement_date.get().value()) : std::string_view("null"))
       << ",priority_time_stamp=" << (msg.fields.priority_time_stamp.get().has_value() ? std::to_string(msg.fields.priority_time_stamp.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_cancelled_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",broker_number=" << (msg.fields.broker_number.get().has_value() ? std::to_string(msg.fields.broker_number.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",order_id=" << (msg.fields.order_id.get().has_value() ? std::to_string(msg.fields.order_id.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_cancelled_terms_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",broker_number=" << (msg.fields.broker_number.get().has_value() ? std::to_string(msg.fields.broker_number.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",order_id=" << (msg.fields.order_id.get().has_value() ? std::to_string(msg.fields.order_id.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_price_time_assigned_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",broker_number=" << (msg.fields.broker_number.get().has_value() ? std::to_string(msg.fields.broker_number.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",order_id=" << (msg.fields.order_id.get().has_value() ? std::to_string(msg.fields.order_id.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",priority_time_stamp=" << (msg.fields.priority_time_stamp.get().has_value() ? std::to_string(msg.fields.priority_time_stamp.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_price_time_assigned_terms_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",broker_number=" << (msg.fields.broker_number.get().has_value() ? std::to_string(msg.fields.broker_number.get().value()) : std::string_view("null"))
       << ",order_side=\"" << xmt_quantumfeedlevel2::order_side::to_string(msg.fields.order_side.get().value()) << '"'
       << ",order_id=" << (msg.fields.order_id.get().has_value() ? std::to_string(msg.fields.order_id.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",priority_time_stamp=" << (msg.fields.priority_time_stamp.get().has_value() ? std::to_string(msg.fields.priority_time_stamp.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const stock_status_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",comment=\"" << msg.fields.comment.get_trimmed().value() << '"'
       << ",stock_state=\"" << msg.fields.stock_state.get_trimmed().value() << '"'
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       << ",listing_market=\"" << xmt_quantumfeedlevel2::listing_market::to_string(msg.fields.listing_market.get().value()) << '"'
       << ",product_type=\"" << xmt_quantumfeedlevel2::product_type::to_string(msg.fields.product_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_report_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trade_number=" << (msg.fields.trade_number.get().has_value() ? std::to_string(msg.fields.trade_number.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",buy_broker_number=" << (msg.fields.buy_broker_number.get().has_value() ? std::to_string(msg.fields.buy_broker_number.get().value()) : std::string_view("null"))
       << ",buy_order_id=" << (msg.fields.buy_order_id.get().has_value() ? std::to_string(msg.fields.buy_order_id.get().value()) : std::string_view("null"))
       << ",buy_display_volume=" << (msg.fields.buy_display_volume.get().has_value() ? std::to_string(msg.fields.buy_display_volume.get().value()) : std::string_view("null"))
       << ",sell_broker_number=" << (msg.fields.sell_broker_number.get().has_value() ? std::to_string(msg.fields.sell_broker_number.get().value()) : std::string_view("null"))
       << ",sell_order_id=" << (msg.fields.sell_order_id.get().has_value() ? std::to_string(msg.fields.sell_order_id.get().value()) : std::string_view("null"))
       << ",sell_display_volume=" << (msg.fields.sell_display_volume.get().has_value() ? std::to_string(msg.fields.sell_display_volume.get().value()) : std::string_view("null"))
       << ",bypass=\"" << xmt_quantumfeedlevel2::bypass::to_string(msg.fields.bypass.get().value()) << '"'
       << ",trade_time_stamp=" << (msg.fields.trade_time_stamp.get().has_value() ? std::to_string(msg.fields.trade_time_stamp.get().value()) : std::string_view("null"))
       << ",cross_type=\"" << xmt_quantumfeedlevel2::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       << ",listing_market=\"" << xmt_quantumfeedlevel2::listing_market::to_string(msg.fields.listing_market.get().value()) << '"'
       << ",product_type=\"" << xmt_quantumfeedlevel2::product_type::to_string(msg.fields.product_type.get().value()) << '"'
       << ",trade_date=" << (msg.fields.trade_date.get().has_value() ? std::to_string(msg.fields.trade_date.get().value()) : std::string_view("null"))
       << ",is_mid_only=\"" << xmt_quantumfeedlevel2::is_mid_only::to_string(msg.fields.is_mid_only.get().value()) << '"'
       << ",is_dark=\"" << xmt_quantumfeedlevel2::is_dark::to_string(msg.fields.is_dark.get().value()) << '"'
       << ",is_conditional=\"" << xmt_quantumfeedlevel2::is_conditional::to_string(msg.fields.is_conditional.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_report_terms_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trade_number=" << (msg.fields.trade_number.get().has_value() ? std::to_string(msg.fields.trade_number.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",buy_broker_number=" << (msg.fields.buy_broker_number.get().has_value() ? std::to_string(msg.fields.buy_broker_number.get().value()) : std::string_view("null"))
       << ",buy_order_id=" << (msg.fields.buy_order_id.get().has_value() ? std::to_string(msg.fields.buy_order_id.get().value()) : std::string_view("null"))
       << ",buy_display_volume=" << (msg.fields.buy_display_volume.get().has_value() ? std::to_string(msg.fields.buy_display_volume.get().value()) : std::string_view("null"))
       << ",sell_broker_number=" << (msg.fields.sell_broker_number.get().has_value() ? std::to_string(msg.fields.sell_broker_number.get().value()) : std::string_view("null"))
       << ",sell_order_id=" << (msg.fields.sell_order_id.get().has_value() ? std::to_string(msg.fields.sell_order_id.get().value()) : std::string_view("null"))
       << ",sell_display_volume=" << (msg.fields.sell_display_volume.get().has_value() ? std::to_string(msg.fields.sell_display_volume.get().value()) : std::string_view("null"))
       << ",trade_time_stamp=" << (msg.fields.trade_time_stamp.get().has_value() ? std::to_string(msg.fields.trade_time_stamp.get().value()) : std::string_view("null"))
       << ",non_resident=\"" << xmt_quantumfeedlevel2::non_resident::to_string(msg.fields.non_resident.get().value()) << '"'
       << ",settlement_terms=\"" << xmt_quantumfeedlevel2::settlement_terms::to_string(msg.fields.settlement_terms.get().value()) << '"'
       << ",settlement_date=" << (msg.fields.settlement_date.get().has_value() ? std::to_string(msg.fields.settlement_date.get().value()) : std::string_view("null"))
       << ",cross_type=\"" << xmt_quantumfeedlevel2::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancelled_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trade_number=" << (msg.fields.trade_number.get().has_value() ? std::to_string(msg.fields.trade_number.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       << ",listing_market=\"" << xmt_quantumfeedlevel2::listing_market::to_string(msg.fields.listing_market.get().value()) << '"'
       << ",product_type=\"" << xmt_quantumfeedlevel2::product_type::to_string(msg.fields.product_type.get().value()) << '"'
       << ",trade_date=" << (msg.fields.trade_date.get().has_value() ? std::to_string(msg.fields.trade_date.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_cancelled_terms_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trade_number=" << (msg.fields.trade_number.get().has_value() ? std::to_string(msg.fields.trade_number.get().value()) : std::string_view("null"))
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_correction_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trade_number=" << (msg.fields.trade_number.get().has_value() ? std::to_string(msg.fields.trade_number.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",buy_broker_number=" << (msg.fields.buy_broker_number.get().has_value() ? std::to_string(msg.fields.buy_broker_number.get().value()) : std::string_view("null"))
       << ",sell_broker_number=" << (msg.fields.sell_broker_number.get().has_value() ? std::to_string(msg.fields.sell_broker_number.get().value()) : std::string_view("null"))
       << ",initiated_by=\"" << xmt_quantumfeedlevel2::initiated_by::to_string(msg.fields.initiated_by.get().value()) << '"'
       << ",orig_trade_number=" << (msg.fields.orig_trade_number.get().has_value() ? std::to_string(msg.fields.orig_trade_number.get().value()) : std::string_view("null"))
       << ",bypass=\"" << xmt_quantumfeedlevel2::bypass::to_string(msg.fields.bypass.get().value()) << '"'
       << ",trade_time_stamp=" << (msg.fields.trade_time_stamp.get().has_value() ? std::to_string(msg.fields.trade_time_stamp.get().value()) : std::string_view("null"))
       << ",cross_type=\"" << xmt_quantumfeedlevel2::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       << ",listing_market=\"" << xmt_quantumfeedlevel2::listing_market::to_string(msg.fields.listing_market.get().value()) << '"'
       << ",product_type=\"" << xmt_quantumfeedlevel2::product_type::to_string(msg.fields.product_type.get().value()) << '"'
       << ",trade_date=" << (msg.fields.trade_date.get().has_value() ? std::to_string(msg.fields.trade_date.get().value()) : std::string_view("null"))
       << ",is_mid_only=\"" << xmt_quantumfeedlevel2::is_mid_only::to_string(msg.fields.is_mid_only.get().value()) << '"'
       << ",is_dark=\"" << xmt_quantumfeedlevel2::is_dark::to_string(msg.fields.is_dark.get().value()) << '"'
       << ",is_conditional=\"" << xmt_quantumfeedlevel2::is_conditional::to_string(msg.fields.is_conditional.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_correction_terms_message& msg) {
    os << "symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",trade_number=" << (msg.fields.trade_number.get().has_value() ? std::to_string(msg.fields.trade_number.get().value()) : std::string_view("null"))
       << ",price=" << (msg.fields.price.get().has_value() ? std::to_string(msg.fields.price.get().value()) : std::string_view("null"))
       << ",volume=" << (msg.fields.volume.get().has_value() ? std::to_string(msg.fields.volume.get().value()) : std::string_view("null"))
       << ",buy_broker_number=" << (msg.fields.buy_broker_number.get().has_value() ? std::to_string(msg.fields.buy_broker_number.get().value()) : std::string_view("null"))
       << ",sell_broker_number=" << (msg.fields.sell_broker_number.get().has_value() ? std::to_string(msg.fields.sell_broker_number.get().value()) : std::string_view("null"))
       << ",initiated_by=\"" << xmt_quantumfeedlevel2::initiated_by::to_string(msg.fields.initiated_by.get().value()) << '"'
       << ",orig_trade_number=" << (msg.fields.orig_trade_number.get().has_value() ? std::to_string(msg.fields.orig_trade_number.get().value()) : std::string_view("null"))
       << ",trade_time_stamp=" << (msg.fields.trade_time_stamp.get().has_value() ? std::to_string(msg.fields.trade_time_stamp.get().value()) : std::string_view("null"))
       << ",non_resident=\"" << xmt_quantumfeedlevel2::non_resident::to_string(msg.fields.non_resident.get().value()) << '"'
       << ",settlement_terms=\"" << xmt_quantumfeedlevel2::settlement_terms::to_string(msg.fields.settlement_terms.get().value()) << '"'
       << ",settlement_date=" << (msg.fields.settlement_date.get().has_value() ? std::to_string(msg.fields.settlement_date.get().value()) : std::string_view("null"))
       << ",cross_type=\"" << xmt_quantumfeedlevel2::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",trading_system_time_stamp=" << (msg.fields.trading_system_time_stamp.get().has_value() ? std::to_string(msg.fields.trading_system_time_stamp.get().value()) : std::string_view("null"))
       ;
    return os;
}

}
