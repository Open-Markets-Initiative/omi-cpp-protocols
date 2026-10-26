#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

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
        case message_type::enum_type::order_book_trading_action_message:
            handler.on_message(*order_book_trading_action_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_book_directory_message:
            handler.on_message(*order_book_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_message:
            handler.on_message(*add_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_mpid_attribution_message:
            handler.on_message(*add_order_mpid_attribution_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_with_price_message:
            handler.on_message(*order_executed_with_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_cancel_message:
            handler.on_message(*order_cancel_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_delete_message:
            handler.on_message(*order_delete_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_book_flush_message:
            handler.on_message(*order_book_flush_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_replace_message:
            handler.on_message(*order_replace_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_message:
            handler.on_message(*trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::cross_trade_message:
            handler.on_message(*cross_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::broken_trade_message:
            handler.on_message(*broken_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::noii_message:
            handler.on_message(*noii_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::moii_message:
            handler.on_message(*moii_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::execution_summary_message:
            handler.on_message(*execution_summary_message::parse(buffer), packet_receive_time, transport);
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
