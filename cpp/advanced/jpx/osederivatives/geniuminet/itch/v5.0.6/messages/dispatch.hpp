#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

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
        case message_type::enum_type::order_book_directory:
            handler.on_message(*order_book_directory::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::combination_orderbook_leg:
            handler.on_message(*combination_orderbook_leg::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::tick_size_table_entry:
            handler.on_message(*tick_size_table_entry::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::system_event_message:
            handler.on_message(*system_event_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_book_state_message:
            handler.on_message(*order_book_state_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_no_mpid:
            handler.on_message(*add_order_no_mpid::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_with_mpid:
            handler.on_message(*add_order_with_mpid::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_with_price_message:
            handler.on_message(*order_executed_with_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_replace_message:
            handler.on_message(*order_replace_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_delete_message:
            handler.on_message(*order_delete_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_message:
            handler.on_message(*trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::equilibrium_price_update:
            handler.on_message(*equilibrium_price_update::parse(buffer), packet_receive_time, transport);
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
