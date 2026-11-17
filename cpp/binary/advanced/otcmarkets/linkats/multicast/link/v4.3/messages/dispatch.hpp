// OtcMarkets.LinkAts.Multicast.Link.v4.3: messages/dispatch.hpp
#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::start_of_spin_message:
            handler.on_message(*start_of_spin_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::end_of_spin_message:
            handler.on_message(*end_of_spin_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::market_open_message:
            handler.on_message(*market_open_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::market_close_message:
            handler.on_message(*market_close_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::security_message:
            handler.on_message(*security_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::quote_message:
            handler.on_message(*quote_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::quote_update_message:
            handler.on_message(*quote_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::inside_message:
            handler.on_message(*inside_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::inside_update_message:
            handler.on_message(*inside_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::reference_price_message:
            handler.on_message(*reference_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::reference_price_update_message:
            handler.on_message(*reference_price_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::extended_security_message:
            handler.on_message(*extended_security_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::extended_security_no_cusip_message:
            handler.on_message(*extended_security_no_cusip_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_message:
            handler.on_message(*trade_message::parse(buffer), packet_receive_time, transport);
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
