#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::seconds_timestamp_message:
            handler.on_message(*seconds_timestamp_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trading_status_message:
            handler.on_message(*trading_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::execution_summary_message:
            handler.on_message(*execution_summary_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_message:
            handler.on_message(*add_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_with_price_message:
            handler.on_message(*order_executed_with_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_delete_message:
            handler.on_message(*order_delete_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::reset_message:
            handler.on_message(*reset_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::communication_control_message:
            handler.on_message(*communication_control_message::parse(buffer), packet_receive_time, transport);
            break;
        default:
            // Unknown message type - handler should implement on_unknown if needed
            break;
    }
}

// Dispatch for the Tcp Packet tree
template<typename Handler>
void dispatch_tcp_packet(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (login_request_message::parse(buffer)->header.packet_type.get().value()) {
        case packet_type::enum_type::login_request_message:
            handler.on_message(*login_request_message::parse(buffer));
            break;
        case packet_type::enum_type::login_result_message:
            handler.on_message(*login_result_message::parse(buffer));
            break;
        case packet_type::enum_type::message_response_message:
            handler.on_message(*message_response_message::parse(buffer));
            break;
        case packet_type::enum_type::end_of_message_message:
            handler.on_message(*end_of_message_message::parse(buffer));
            break;
        default:
            // Unknown message type - handler should implement on_unknown if needed
            break;
    }
}

}
