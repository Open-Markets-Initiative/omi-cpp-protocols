#pragma once

#include <ostream>
#include <string_view>

#include "SystemEventMessage.hpp"
#include "OrderBookTradingActionMessage.hpp"
#include "OrderBookDirectoryMessage.hpp"
#include "AddOrderMessage.hpp"
#include "AddOrderMpidAttributionMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "OrderExecutedWithPriceMessage.hpp"
#include "OrderCancelMessage.hpp"
#include "OrderDeleteMessage.hpp"
#include "OrderBookFlushMessage.hpp"
#include "OrderReplaceMessage.hpp"
#include "TradeMessage.hpp"
#include "CrossTradeMessage.hpp"
#include "BrokenTradeMessage.hpp"
#include "NoiiMessage.hpp"
#include "MoiiMessage.hpp"
#include "ExecutionSummaryMessage.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

namespace itch_totalview = ::nasdaq::nordicequities::totalview::itch::v3_04_x;

inline std::ostream& operator<<(std::ostream& os, const packet_header& value) {
    os << "session=\"" << value.session.get_trimmed().value() << '"'
       << ",sequence_number=" << value.sequence_number.get().value()
       << ",message_count=" << value.message_count.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const message_header& value) {
    os << "message_length=" << value.message_length.get().value()
       << ",message_type=\"" << itch_totalview::message_type::to_string(value.message_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",event_code=\"" << itch_totalview::event_code::to_string(msg.fields.event_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_trading_action_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_book=" << msg.fields.order_book.get().value()
       << ",symbol_state=\"" << itch_totalview::symbol_state::to_string(msg.fields.symbol_state.get().value()) << '"'
       << ",extension=\"" << itch_totalview::extension::to_string(msg.fields.extension.get().value()) << '"'
       << ",reason=\"" << msg.fields.reason.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_directory_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_book=" << msg.fields.order_book.get().value()
       << ",symbol=\"" << msg.fields.symbol.get_trimmed().value() << '"'
       << ",isin=\"" << msg.fields.isin.get_trimmed().value() << '"'
       << ",financial_product=\"" << itch_totalview::financial_product::to_string(msg.fields.financial_product.get().value()) << '"'
       << ",trading_currency=\"" << msg.fields.trading_currency.get_trimmed().value() << '"'
       << ",mic=\"" << msg.fields.mic.get_trimmed().value() << '"'
       << ",market_segment_id=" << msg.fields.market_segment_id.get().value()
       << ",note_codes_bit_field_1=" << static_cast<unsigned>(msg.fields.note_codes_bit_field_1.get().value())
       << ",note_codes_bit_field_2=" << static_cast<unsigned>(msg.fields.note_codes_bit_field_2.get().value())
       << ",note_codes_bit_field_3=" << static_cast<unsigned>(msg.fields.note_codes_bit_field_3.get().value())
       << ",note_codes_bit_field_4=" << static_cast<unsigned>(msg.fields.note_codes_bit_field_4.get().value())
       << ",note_codes_bit_field_5=" << static_cast<unsigned>(msg.fields.note_codes_bit_field_5.get().value())
       << ",note_codes_bit_field_6=" << static_cast<unsigned>(msg.fields.note_codes_bit_field_6.get().value())
       << ",note_codes_bit_field_7=" << static_cast<unsigned>(msg.fields.note_codes_bit_field_7.get().value())
       << ",note_codes_bit_field_8=" << static_cast<unsigned>(msg.fields.note_codes_bit_field_8.get().value())
       << ",round_lot_size=" << msg.fields.round_lot_size.get().value()
       << ",nordic_mid_mic=\"" << msg.fields.nordic_mid_mic.get_trimmed().value() << '"'
       << ",aod_mic=\"" << msg.fields.aod_mic.get_trimmed().value() << '"'
       << ",notation_of_qty=\"" << msg.fields.notation_of_qty.get_trimmed().value() << '"'
       << ",notional_amount=" << msg.fields.notional_amount.get().value()
       << ",currency=\"" << msg.fields.currency.get_trimmed().value() << '"'
       << ",price_notation=\"" << itch_totalview::price_notation::to_string(msg.fields.price_notation.get().value()) << '"'
       << ",multiplier_for_calculating_quantity_in_measurement_unit=" << msg.fields.multiplier_for_calculating_quantity_in_measurement_unit.get().value()
       << ",pure_stream_mic=\"" << msg.fields.pure_stream_mic.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",buy_sell_indicator=\"" << itch_totalview::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",order_book=" << msg.fields.order_book.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const add_order_mpid_attribution_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",buy_sell_indicator=\"" << itch_totalview::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",order_book=" << msg.fields.order_book.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",attribution=\"" << msg.fields.attribution.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       << ",mpid=\"" << msg.fields.mpid.get_trimmed().value() << '"'
       << ",mpid_counterparty=\"" << msg.fields.mpid_counterparty.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_with_price_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       << ",printable=\"" << itch_totalview::printable::to_string(msg.fields.printable.get().value()) << '"'
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",mpid_owner=\"" << msg.fields.mpid_owner.get_trimmed().value() << '"'
       << ",mpid_counterparty=\"" << msg.fields.mpid_counterparty.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_cancel_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",canceled_quantity=" << msg.fields.canceled_quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_delete_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_book_flush_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_book=" << msg.fields.order_book.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_replace_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",original_order_reference_number=" << msg.fields.original_order_reference_number.get().value()
       << ",new_order_reference_number=" << msg.fields.new_order_reference_number.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const trade_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_reference_number=" << msg.fields.order_reference_number.get().value()
       << ",trade_type=\"" << itch_totalview::trade_type::to_string(msg.fields.trade_type.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",order_book=" << msg.fields.order_book.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       << ",trade_price=" << msg.fields.trade_price.get().value()
       << ",participant_id_buyer=\"" << msg.fields.participant_id_buyer.get_trimmed().value() << '"'
       << ",participant_id_seller=\"" << msg.fields.participant_id_seller.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cross_trade_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",order_book=" << msg.fields.order_book.get().value()
       << ",cross_price=" << msg.fields.cross_price.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       << ",cross_type=\"" << itch_totalview::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",number_of_trades=" << msg.fields.number_of_trades.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const broken_trade_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",match_number=" << msg.fields.match_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const noii_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",paired_quantity=" << msg.fields.paired_quantity.get().value()
       << ",imbalance_quantity=" << msg.fields.imbalance_quantity.get().value()
       << ",imbalance_direction=\"" << itch_totalview::imbalance_direction::to_string(msg.fields.imbalance_direction.get().value()) << '"'
       << ",order_book=" << msg.fields.order_book.get().value()
       << ",equilibrium_price=" << msg.fields.equilibrium_price.get().value()
       << ",cross_type=\"" << itch_totalview::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",best_bid_price=" << msg.fields.best_bid_price.get().value()
       << ",best_bid_quantity=" << msg.fields.best_bid_quantity.get().value()
       << ",best_ask_price=" << msg.fields.best_ask_price.get().value()
       << ",best_ask_quantity=" << msg.fields.best_ask_quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const moii_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",paired_quantity=" << msg.fields.paired_quantity.get().value()
       << ",order_book=" << msg.fields.order_book.get().value()
       << ",equilibrium_price=" << msg.fields.equilibrium_price.get().value()
       << ",cross_type=\"" << itch_totalview::cross_type::to_string(msg.fields.cross_type.get().value()) << '"'
       << ",cross_level=\"" << itch_totalview::cross_level::to_string(msg.fields.cross_level.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const execution_summary_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",tracking_number=" << msg.fields.tracking_number.get().value()
       << ",order_book=" << msg.fields.order_book.get().value()
       << ",aggressing_side=\"" << itch_totalview::aggressing_side::to_string(msg.fields.aggressing_side.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",hidden_quantity=" << msg.fields.hidden_quantity.get().value()
       << ",stp_cancel_quantity=" << msg.fields.stp_cancel_quantity.get().value()
       << ",far_price=" << msg.fields.far_price.get().value()
       << ",add_quantity=" << msg.fields.add_quantity.get().value()
       << ",number_of_lit_executions=" << msg.fields.number_of_lit_executions.get().value()
       ;
    return os;
}

}
