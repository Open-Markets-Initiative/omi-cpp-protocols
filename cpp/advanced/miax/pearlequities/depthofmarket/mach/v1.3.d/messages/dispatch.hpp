#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/ApplicationMessage.hpp"
#include "../structs/MachMessage.hpp"
#include "../types/MachPacketLength.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const mach_message& transport) {
    (void)length;

    switch (system_time_message::parse(buffer)->mach_packet_type.get().value()) {
        case mach_packet_type::enum_type::application_message: {
            switch (system_time_message::parse(buffer)->message_type.get().value()) {
                case message_type::enum_type::system_time_message:
                    handler.on_message(*system_time_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::symbol_update_message:
                    handler.on_message(*symbol_update_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::system_state_message:
                    handler.on_message(*system_state_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::security_trading_status_notification_message:
                    handler.on_message(*security_trading_status_notification_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::symbol_clear_message:
                    handler.on_message(*symbol_clear_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::add_order_message:
                    handler.on_message(*add_order_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::modify_order_message:
                    handler.on_message(*modify_order_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::delete_order_message:
                    handler.on_message(*delete_order_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::order_execution_message:
                    handler.on_message(*order_execution_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::trade_message:
                    handler.on_message(*trade_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::trade_cancel_message:
                    handler.on_message(*trade_cancel_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Message Type
                    break;
            }
            break;
        }
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length, packet_receive_time, transport); }) {
                handler.on_unknown(buffer, length, packet_receive_time, transport);
            }
            break;
    }
}

// Dispatch for the Tcp Packet tree
template<typename Handler>
void dispatch_tcp_packet(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (refresh_request_message::parse(buffer)->header.esesm_packet_type.get().value()) {
        case esesm_packet_type::enum_type::unsequenced_data_packet: {
            switch (refresh_request_message::parse(buffer)->unsequenced_message_type.get().value()) {
                case unsequenced_message_type::enum_type::refresh_request_message:
                    handler.on_message(*refresh_request_message::parse(buffer));
                    break;
                case unsequenced_message_type::enum_type::refresh_response_message:
                    handler.on_message(*refresh_response_message::parse(buffer));
                    break;
                case unsequenced_message_type::enum_type::end_of_refresh_notification_message:
                    handler.on_message(*end_of_refresh_notification_message::parse(buffer));
                    break;
                default:
                    // Unknown Unsequenced Message Type
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
