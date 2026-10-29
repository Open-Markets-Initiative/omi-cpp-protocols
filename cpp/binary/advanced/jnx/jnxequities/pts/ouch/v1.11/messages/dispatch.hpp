#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/ServerPacketHeader.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (debug_packet::parse(buffer)->header.server_packet_type.get().value()) {
        case server_packet_type::enum_type::debug_packet:
            handler.on_message(*debug_packet::parse(buffer));
            break;
        case server_packet_type::enum_type::login_accepted_packet:
            handler.on_message(*login_accepted_packet::parse(buffer));
            break;
        case server_packet_type::enum_type::login_rejected_packet:
            handler.on_message(*login_rejected_packet::parse(buffer));
            break;
        case server_packet_type::enum_type::sequenced_data_packet: {
            switch (system_event_message::parse(buffer)->sequenced_message_type.get().value()) {
                case sequenced_message_type::enum_type::system_event_message:
                    handler.on_message(*system_event_message::parse(buffer));
                    break;
                case sequenced_message_type::enum_type::order_accepted_message:
                    handler.on_message(*order_accepted_message::parse(buffer));
                    break;
                case sequenced_message_type::enum_type::order_replaced_message:
                    handler.on_message(*order_replaced_message::parse(buffer));
                    break;
                case sequenced_message_type::enum_type::order_canceled_message:
                    handler.on_message(*order_canceled_message::parse(buffer));
                    break;
                case sequenced_message_type::enum_type::order_aiq_canceled_message:
                    handler.on_message(*order_aiq_canceled_message::parse(buffer));
                    break;
                case sequenced_message_type::enum_type::order_executed_message:
                    handler.on_message(*order_executed_message::parse(buffer));
                    break;
                case sequenced_message_type::enum_type::order_rejected_message:
                    handler.on_message(*order_rejected_message::parse(buffer));
                    break;
                default:
                    // none of the messages it carries: the Sequenced Data Packet itself
                    handler.on_message(*sequenced_data_packet::parse(buffer));
                    break;
            }
            break;
        }
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

    switch (login_request_packet::parse(buffer)->header.client_packet_type.get().value()) {
        case client_packet_type::enum_type::login_request_packet:
            handler.on_message(*login_request_packet::parse(buffer));
            break;
        case client_packet_type::enum_type::unsequenced_data_packet: {
            switch (enter_order_message::parse(buffer)->unsequenced_message_type.get().value()) {
                case unsequenced_message_type::enum_type::enter_order_message:
                    handler.on_message(*enter_order_message::parse(buffer));
                    break;
                case unsequenced_message_type::enum_type::replace_order_message:
                    handler.on_message(*replace_order_message::parse(buffer));
                    break;
                case unsequenced_message_type::enum_type::cancel_order_message:
                    handler.on_message(*cancel_order_message::parse(buffer));
                    break;
                default:
                    // none of the messages it carries: the Unsequenced Data Packet itself
                    handler.on_message(*unsequenced_data_packet::parse(buffer));
                    break;
            }
            break;
        }
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length); }) {
                handler.on_unknown(buffer, length);
            }
            break;
    }
}

}
