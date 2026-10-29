#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::sequence_number_reset_message:
            handler.on_message(*sequence_number_reset_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::source_time_reference_message:
            handler.on_message(*source_time_reference_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::symbol_index_mapping_message:
            handler.on_message(*symbol_index_mapping_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::symbol_clear_message:
            handler.on_message(*symbol_clear_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::security_status_message:
            handler.on_message(*security_status_message::parse(buffer), packet_receive_time, transport);
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
        case message_type::enum_type::replace_order_message:
            handler.on_message(*replace_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::imbalance_message:
            handler.on_message(*imbalance_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_refresh_message:
            handler.on_message(*add_order_refresh_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::non_displayed_trade_message:
            handler.on_message(*non_displayed_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::cross_trade_message:
            handler.on_message(*cross_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_cancel_message:
            handler.on_message(*trade_cancel_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::cross_correction_message:
            handler.on_message(*cross_correction_message::parse(buffer), packet_receive_time, transport);
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
