#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

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
        case message_type::enum_type::security_status_message:
            handler.on_message(*security_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::refresh_header_message:
            handler.on_message(*refresh_header_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::imbalance_message:
            handler.on_message(*imbalance_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_refresh_message:
            handler.on_message(*add_order_refresh_message::parse(buffer), packet_receive_time, transport);
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
