#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

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
        case message_type::enum_type::complex_strategy_directory_message:
            handler.on_message(*complex_strategy_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::strategy_trading_action_message:
            handler.on_message(*strategy_trading_action_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::strategy_open_closed_message:
            handler.on_message(*strategy_open_closed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::complex_strategy_order_on_book_message:
            handler.on_message(*complex_strategy_order_on_book_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::complex_strategy_auction_message:
            handler.on_message(*complex_strategy_auction_message::parse(buffer), packet_receive_time, transport);
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
