#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::time_message:
            handler.on_message(*time_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::unit_clear_message:
            handler.on_message(*unit_clear_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_long_message:
            handler.on_message(*add_order_long_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_short_message:
            handler.on_message(*add_order_short_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_expanded_message:
            handler.on_message(*add_order_expanded_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_at_price_size_message:
            handler.on_message(*order_executed_at_price_size_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::reduce_size_long_message:
            handler.on_message(*reduce_size_long_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::reduce_size_short_message:
            handler.on_message(*reduce_size_short_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::modify_order_long_message:
            handler.on_message(*modify_order_long_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::modify_order_short_message:
            handler.on_message(*modify_order_short_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::delete_order_message:
            handler.on_message(*delete_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_long_message:
            handler.on_message(*trade_long_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_short_message:
            handler.on_message(*trade_short_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_expanded_message:
            handler.on_message(*trade_expanded_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_break_message:
            handler.on_message(*trade_break_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::end_of_session_message:
            handler.on_message(*end_of_session_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::symbol_mapping_message:
            handler.on_message(*symbol_mapping_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trading_status_message:
            handler.on_message(*trading_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::auction_update_message:
            handler.on_message(*auction_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::auction_summary_message:
            handler.on_message(*auction_summary_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::retail_price_improvement_message:
            handler.on_message(*retail_price_improvement_message::parse(buffer), packet_receive_time, transport);
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
