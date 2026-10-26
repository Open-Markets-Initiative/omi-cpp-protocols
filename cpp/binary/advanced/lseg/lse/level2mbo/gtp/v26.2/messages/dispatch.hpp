#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/UnitHeader.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const unit_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::system_event_message:
            handler.on_message(*system_event_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::instrument_directory_message:
            handler.on_message(*instrument_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::instrument_status_message:
            handler.on_message(*instrument_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_mbo_message:
            handler.on_message(*add_order_mbo_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_short_mbo_message:
            handler.on_message(*add_order_short_mbo_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_book_clear_message:
            handler.on_message(*order_book_clear_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_message:
            handler.on_message(*trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::statistics_message:
            handler.on_message(*statistics_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::statistics_update_message:
            handler.on_message(*statistics_update_message::parse(buffer), packet_receive_time, transport);
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
