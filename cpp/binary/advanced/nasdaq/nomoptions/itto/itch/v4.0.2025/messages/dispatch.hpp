#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::system_event_message:
            handler.on_message(*system_event_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_directory_message:
            handler.on_message(*options_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trading_action_message:
            handler.on_message(*trading_action_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::security_open_message:
            handler.on_message(*security_open_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_message_short_message_form:
            handler.on_message(*add_order_message_short_message_form::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_message_long_form_message:
            handler.on_message(*add_order_message_long_form_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_quote_message_short_form_message:
            handler.on_message(*add_quote_message_short_form_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_quote_message_long_form_message:
            handler.on_message(*add_quote_message_long_form_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::single_side_executed_message:
            handler.on_message(*single_side_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::single_side_executed_with_price_message:
            handler.on_message(*single_side_executed_with_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_cancel_message:
            handler.on_message(*order_cancel_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::single_side_replace_message_short_form:
            handler.on_message(*single_side_replace_message_short_form::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::single_side_replace_message_long_form:
            handler.on_message(*single_side_replace_message_long_form::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::single_side_delete_message:
            handler.on_message(*single_side_delete_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::single_side_change_message:
            handler.on_message(*single_side_change_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::quote_replace_message_short_form:
            handler.on_message(*quote_replace_message_short_form::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::quote_replace_message_long_form:
            handler.on_message(*quote_replace_message_long_form::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::quote_delete_message:
            handler.on_message(*quote_delete_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_trade_messages_non_auction:
            handler.on_message(*options_trade_messages_non_auction::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_cross_trade_message:
            handler.on_message(*options_cross_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::broken_trade_order_executed_message:
            handler.on_message(*broken_trade_order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::noii_message:
            handler.on_message(*noii_message::parse(buffer), packet_receive_time, transport);
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
        case server_packet_type::enum_type::sequenced_data_packet: {
            switch (end_of_replay_sequence_message::parse(buffer)->sequenced_message_type.get().value()) {
                case sequenced_message_type::enum_type::end_of_replay_sequence_message:
                    handler.on_message(*end_of_replay_sequence_message::parse(buffer));
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
