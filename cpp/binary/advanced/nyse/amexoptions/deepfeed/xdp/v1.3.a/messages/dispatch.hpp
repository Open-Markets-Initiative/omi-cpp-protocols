#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::outright_market_depth_buy_message:
            handler.on_message(*outright_market_depth_buy_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::outright_market_depth_sell_message:
            handler.on_message(*outright_market_depth_sell_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::underlying_status_message:
            handler.on_message(*underlying_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::outright_series_status_message:
            handler.on_message(*outright_series_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::refresh_outright_market_depth_buy_message:
            handler.on_message(*refresh_outright_market_depth_buy_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::refresh_outright_market_depth_sell_message:
            handler.on_message(*refresh_outright_market_depth_sell_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::underlying_index_mapping_message:
            handler.on_message(*underlying_index_mapping_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::series_index_mapping_message:
            handler.on_message(*series_index_mapping_message::parse(buffer), packet_receive_time, transport);
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
