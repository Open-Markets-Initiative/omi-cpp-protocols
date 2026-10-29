#pragma once

#include <ostream>
#include <string_view>

#include "DebugPacket.hpp"
#include "LoginRequestPacket.hpp"
#include "UnsequencedDataPacket.hpp"
#include "EnterOrderMessage.hpp"
#include "ReplaceOrderMessage.hpp"
#include "CancelOrderMessage.hpp"
#include "LoginAcceptedPacket.hpp"
#include "LoginRejectedPacket.hpp"
#include "SequencedDataPacket.hpp"
#include "SystemEventMessage.hpp"
#include "OrderAcceptedMessage.hpp"
#include "OrderReplacedMessage.hpp"
#include "OrderCanceledMessage.hpp"
#include "OrderAiqCanceledMessage.hpp"
#include "OrderExecutedMessage.hpp"
#include "OrderRejectedMessage.hpp"
#include "../json/messages/debug_packet_json.hpp"
#include "../json/messages/unsequenced_data_packet_json.hpp"
#include "../json/messages/sequenced_data_packet_json.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

namespace ouch_pts = ::jnx::jnxequities::pts::ouch::v1_11;

inline std::ostream& operator<<(std::ostream& os, const client_packet_header& value) {
    os << "packet_length=" << value.packet_length.get().value()
       << ",client_packet_type=\"" << ouch_pts::client_packet_type::to_string(value.client_packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const server_packet_header& value) {
    os << "packet_length=" << value.packet_length.get().value()
       << ",server_packet_type=\"" << ouch_pts::server_packet_type::to_string(value.server_packet_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const debug_packet& msg) {
    os << "tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_request_packet& msg) {
    os << "username=\"" << msg.fields.username.get_trimmed().value() << '"'
       << ",password=\"" << msg.fields.password.get_trimmed().value() << '"'
       << ",requested_session=\"" << msg.fields.requested_session.get_trimmed().value() << '"'
       << ",requested_sequence_number=\"" << msg.fields.requested_sequence_number.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const unsequenced_data_packet& msg) {
    os << "unsequenced_message_type=\"" << ouch_pts::unsequenced_message_type::to_string(msg.fields.unsequenced_message_type.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const enter_order_message& msg) {
    os << "order_token=" << msg.fields.order_token.get().value()
       << ",client_reference=\"" << msg.fields.client_reference.get_trimmed().value() << '"'
       << ",buy_sell_indicator=\"" << ouch_pts::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",orderbook_id=" << msg.fields.orderbook_id.get().value()
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",time_in_force=\"" << ouch_pts::time_in_force::to_string(msg.fields.time_in_force.get().value()) << '"'
       << ",firm_id=" << msg.fields.firm_id.get().value()
       << ",display=\"" << ouch_pts::display::to_string(msg.fields.display.get().value()) << '"'
       << ",capacity=\"" << ouch_pts::capacity::to_string(msg.fields.capacity.get().value()) << '"'
       << ",minimum_quantity=" << msg.fields.minimum_quantity.get().value()
       << ",order_classification=\"" << ouch_pts::order_classification::to_string(msg.fields.order_classification.get().value()) << '"'
       << ",cash_margin_type=\"" << ouch_pts::cash_margin_type::to_string(msg.fields.cash_margin_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const replace_order_message& msg) {
    os << "existing_order_token=" << msg.fields.existing_order_token.get().value()
       << ",replacement_order_token=" << msg.fields.replacement_order_token.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",price=" << msg.fields.price.get().value()
       << ",time_in_force=\"" << ouch_pts::time_in_force::to_string(msg.fields.time_in_force.get().value()) << '"'
       << ",display=\"" << ouch_pts::display::to_string(msg.fields.display.get().value()) << '"'
       << ",minimum_quantity=" << msg.fields.minimum_quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const cancel_order_message& msg) {
    os << "order_token=" << msg.fields.order_token.get().value()
       << ",quantity=" << msg.fields.quantity.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_accepted_packet& msg) {
    os << "accepted_session=\"" << msg.fields.accepted_session.get_trimmed().value() << '"'
       << ",accepted_sequence_number=\"" << msg.fields.accepted_sequence_number.get_trimmed().value() << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const login_rejected_packet& msg) {
    os << "reject_reason_code=\"" << ouch_pts::reject_reason_code::to_string(msg.fields.reject_reason_code.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const sequenced_data_packet& msg) {
    os << "sequenced_message_type=\"" << ouch_pts::sequenced_message_type::to_string(msg.fields.sequenced_message_type.get().value()) << '"'
       << ",tail=" << json::tail_to_json_string(msg)
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const system_event_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",system_event=\"" << ouch_pts::system_event::to_string(msg.fields.system_event.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_accepted_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",order_token=" << msg.fields.order_token.get().value()
       << ",client_reference=\"" << msg.fields.client_reference.get_trimmed().value() << '"'
       << ",buy_sell_indicator=\"" << ouch_pts::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",orderbook_id=" << msg.fields.orderbook_id.get().value()
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",time_in_force=\"" << ouch_pts::time_in_force::to_string(msg.fields.time_in_force.get().value()) << '"'
       << ",firm_id=" << msg.fields.firm_id.get().value()
       << ",display=\"" << ouch_pts::display::to_string(msg.fields.display.get().value()) << '"'
       << ",capacity=\"" << ouch_pts::capacity::to_string(msg.fields.capacity.get().value()) << '"'
       << ",order_number=" << msg.fields.order_number.get().value()
       << ",minimum_quantity=" << msg.fields.minimum_quantity.get().value()
       << ",order_state=\"" << ouch_pts::order_state::to_string(msg.fields.order_state.get().value()) << '"'
       << ",order_classification=\"" << ouch_pts::order_classification::to_string(msg.fields.order_classification.get().value()) << '"'
       << ",cash_margin_type=\"" << ouch_pts::cash_margin_type::to_string(msg.fields.cash_margin_type.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_replaced_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",replacement_order_token=" << msg.fields.replacement_order_token.get().value()
       << ",buy_sell_indicator=\"" << ouch_pts::buy_sell_indicator::to_string(msg.fields.buy_sell_indicator.get().value()) << '"'
       << ",quantity=" << msg.fields.quantity.get().value()
       << ",orderbook_id=" << msg.fields.orderbook_id.get().value()
       << ",group=\"" << msg.fields.group.get_trimmed().value() << '"'
       << ",price=" << msg.fields.price.get().value()
       << ",time_in_force=\"" << ouch_pts::time_in_force::to_string(msg.fields.time_in_force.get().value()) << '"'
       << ",display=\"" << ouch_pts::display::to_string(msg.fields.display.get().value()) << '"'
       << ",order_number=" << msg.fields.order_number.get().value()
       << ",minimum_quantity=" << msg.fields.minimum_quantity.get().value()
       << ",order_state=\"" << ouch_pts::order_state::to_string(msg.fields.order_state.get().value()) << '"'
       << ",previous_order_token=" << msg.fields.previous_order_token.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_canceled_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",order_token=" << msg.fields.order_token.get().value()
       << ",decrement_quantity=" << msg.fields.decrement_quantity.get().value()
       << ",order_canceled_reason=\"" << ouch_pts::order_canceled_reason::to_string(msg.fields.order_canceled_reason.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_aiq_canceled_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",order_token=" << msg.fields.order_token.get().value()
       << ",decrement_quantity=" << msg.fields.decrement_quantity.get().value()
       << ",order_canceled_reason=\"" << ouch_pts::order_canceled_reason::to_string(msg.fields.order_canceled_reason.get().value()) << '"'
       << ",quantity_prevented_from_trading=" << msg.fields.quantity_prevented_from_trading.get().value()
       << ",execution_price=" << msg.fields.execution_price.get().value()
       << ",liquidity_indicator=\"" << ouch_pts::liquidity_indicator::to_string(msg.fields.liquidity_indicator.get().value()) << '"'
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_executed_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",order_token=" << msg.fields.order_token.get().value()
       << ",executed_quantity=" << msg.fields.executed_quantity.get().value()
       << ",execution_price=" << msg.fields.execution_price.get().value()
       << ",liquidity_indicator=\"" << ouch_pts::liquidity_indicator::to_string(msg.fields.liquidity_indicator.get().value()) << '"'
       << ",match_number=" << msg.fields.match_number.get().value()
       ;
    return os;
}

inline std::ostream& operator<<(std::ostream& os, const order_rejected_message& msg) {
    os << "timestamp=" << msg.fields.timestamp.get().value()
       << ",order_token=" << msg.fields.order_token.get().value()
       << ",order_rejected_reason=\"" << ouch_pts::order_rejected_reason::to_string(msg.fields.order_rejected_reason.get().value()) << '"'
       ;
    return os;
}

}
