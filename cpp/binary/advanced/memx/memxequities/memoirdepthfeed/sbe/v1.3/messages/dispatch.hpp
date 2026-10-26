#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/SbeHeader.hpp"
#include "../structs/CommonHeader.hpp"
#include "../types/MessageLength.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const common_header& transport) {
    (void)length;
    const auto* header = sbe_header::parse(buffer + sizeof(sbe_memoirdepthfeed::message_length));

    switch (header->template_id.get().value()) {
        case template_id::enum_type::instrument_directory_message:
            handler.on_message(*instrument_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::reg_sho_restriction_message:
            handler.on_message(*reg_sho_restriction_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::security_trading_status_message:
            handler.on_message(*security_trading_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::trading_session_status_message:
            handler.on_message(*trading_session_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_added_message:
            handler.on_message(*order_added_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_deleted_message:
            handler.on_message(*order_deleted_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_reduced_message:
            handler.on_message(*order_reduced_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::trade_message:
            handler.on_message(*trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::broken_trade_message:
            handler.on_message(*broken_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::corrected_trade_message:
            handler.on_message(*corrected_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::clear_book_message:
            handler.on_message(*clear_book_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::snapshot_complete_message:
            handler.on_message(*snapshot_complete_message::parse(buffer), packet_receive_time, transport);
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
