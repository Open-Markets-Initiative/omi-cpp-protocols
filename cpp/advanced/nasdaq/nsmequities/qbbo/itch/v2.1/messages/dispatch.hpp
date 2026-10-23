#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

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
        case message_type::enum_type::stock_directory_message:
            handler.on_message(*stock_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::stock_trading_action_message:
            handler.on_message(*stock_trading_action_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::reg_sho_restriction_message:
            handler.on_message(*reg_sho_restriction_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::mwcb_decline_level_message:
            handler.on_message(*mwcb_decline_level_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::mwcb_breach_message:
            handler.on_message(*mwcb_breach_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::operational_halt_message:
            handler.on_message(*operational_halt_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::bbo_quotation_message:
            handler.on_message(*bbo_quotation_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::price_improvement_message:
            handler.on_message(*price_improvement_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::ipo_quoting_period_update_message:
            handler.on_message(*ipo_quoting_period_update_message::parse(buffer), packet_receive_time, transport);
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
