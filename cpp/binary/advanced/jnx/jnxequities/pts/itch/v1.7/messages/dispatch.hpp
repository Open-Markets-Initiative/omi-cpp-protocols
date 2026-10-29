#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::seconds_message:
            handler.on_message(*seconds_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::system_event_message:
            handler.on_message(*system_event_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::price_tick_size_message:
            handler.on_message(*price_tick_size_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::orderbook_directory_message:
            handler.on_message(*orderbook_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trading_state_message:
            handler.on_message(*trading_state_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::short_selling_price_restriction_state_message:
            handler.on_message(*short_selling_price_restriction_state_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_added_without_attributes_message:
            handler.on_message(*order_added_without_attributes_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_added_with_attributes_message:
            handler.on_message(*order_added_with_attributes_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_deleted_message:
            handler.on_message(*order_deleted_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_replaced_message:
            handler.on_message(*order_replaced_message::parse(buffer), packet_receive_time, transport);
            break;
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length, packet_receive_time, transport); }) {
                handler.on_unknown(buffer, length, packet_receive_time, transport);
            }
            break;
    }
}

// Dispatch for the Server Packet tree
template<typename Handler>
void dispatch_server_packet(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (login_accepted_packet::parse(buffer)->header.server_packet_type.get().value()) {
        case server_packet_type::enum_type::login_accepted_packet:
            handler.on_message(*login_accepted_packet::parse(buffer));
            break;
        case server_packet_type::enum_type::login_rejected_packet:
            handler.on_message(*login_rejected_packet::parse(buffer));
            break;
        case server_packet_type::enum_type::sequenced_data_packet:
            handler.on_message(*sequenced_data_packet::parse(buffer));
            break;
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length); }) {
                handler.on_unknown(buffer, length);
            }
            break;
    }
}

// Dispatch for the Client Packet tree
template<typename Handler>
void dispatch_client_packet(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (debug_packet::parse(buffer)->header.client_packet_type.get().value()) {
        case client_packet_type::enum_type::debug_packet:
            handler.on_message(*debug_packet::parse(buffer));
            break;
        case client_packet_type::enum_type::login_request_packet:
            handler.on_message(*login_request_packet::parse(buffer));
            break;
        case client_packet_type::enum_type::unsequenced_data_packet:
            handler.on_message(*unsequenced_data_packet::parse(buffer));
            break;
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length); }) {
                handler.on_unknown(buffer, length);
            }
            break;
    }
}

}
