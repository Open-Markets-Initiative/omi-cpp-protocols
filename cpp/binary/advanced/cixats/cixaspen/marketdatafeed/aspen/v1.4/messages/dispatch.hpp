#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::market_event_message:
            handler.on_message(*market_event_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::symbol_information_message:
            handler.on_message(*symbol_information_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::symbol_state_message:
            handler.on_message(*symbol_state_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::new_order_add_message:
            handler.on_message(*new_order_add_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_partial_cancel_message:
            handler.on_message(*order_partial_cancel_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_cancel_all_message:
            handler.on_message(*order_cancel_all_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_message:
            handler.on_message(*trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_cancel_message:
            handler.on_message(*trade_cancel_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_correct_message:
            handler.on_message(*trade_correct_message::parse(buffer), packet_receive_time, transport);
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
