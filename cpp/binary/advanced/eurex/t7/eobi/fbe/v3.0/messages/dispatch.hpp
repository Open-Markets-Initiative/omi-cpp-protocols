#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/EobiHeader.hpp"
#include "../structs/PacketHeader.hpp"
#include "../types/BodyLen.hpp"

namespace eurex::t7::eobi::fbe::v3_0 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = eobi_header::parse(buffer);

    switch (header->template_id.get().value()) {
        case template_id::enum_type::add_complex_instrument:
            handler.on_message(*add_complex_instrument::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::auction_bbo:
            handler.on_message(*auction_bbo::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::auction_clearing_price:
            handler.on_message(*auction_clearing_price::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::cross_request:
            handler.on_message(*cross_request::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::execution_summary:
            handler.on_message(*execution_summary::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::full_order_execution:
            handler.on_message(*full_order_execution::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::heartbeat:
            handler.on_message(*heartbeat::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::instrument_state_change:
            handler.on_message(*instrument_state_change::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::instrument_summary:
            handler.on_message(*instrument_summary::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_add:
            handler.on_message(*order_add::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_delete:
            handler.on_message(*order_delete::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_mass_delete:
            handler.on_message(*order_mass_delete::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_modify:
            handler.on_message(*order_modify::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_modify_same_prio:
            handler.on_message(*order_modify_same_prio::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::partial_order_execution:
            handler.on_message(*partial_order_execution::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::product_state_change:
            handler.on_message(*product_state_change::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::product_summary:
            handler.on_message(*product_summary::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::quote_request:
            handler.on_message(*quote_request::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::snapshot_order:
            handler.on_message(*snapshot_order::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::top_of_book:
            handler.on_message(*top_of_book::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::trade_report:
            handler.on_message(*trade_report::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::trade_reversal:
            handler.on_message(*trade_reversal::parse(buffer), packet_receive_time, transport);
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
