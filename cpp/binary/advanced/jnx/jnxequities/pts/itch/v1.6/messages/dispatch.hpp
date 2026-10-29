#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

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

}
