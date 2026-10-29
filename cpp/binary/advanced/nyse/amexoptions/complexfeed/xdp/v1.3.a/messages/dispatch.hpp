#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::complex_quote_message:
            handler.on_message(*complex_quote_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::complex_trade_message:
            handler.on_message(*complex_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::complex_crossing_rfq_message:
            handler.on_message(*complex_crossing_rfq_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::complex_cube_rfq_message:
            handler.on_message(*complex_cube_rfq_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::complex_status_message:
            handler.on_message(*complex_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::refresh_complex_quote_message:
            handler.on_message(*refresh_complex_quote_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::refresh_complex_trade_message:
            handler.on_message(*refresh_complex_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::complex_symbol_definition_message:
            handler.on_message(*complex_symbol_definition_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::stream_id_message:
            handler.on_message(*stream_id_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::sequence_number_reset_message:
            handler.on_message(*sequence_number_reset_message::parse(buffer), packet_receive_time, transport);
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
