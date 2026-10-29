#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/EobiHeader.hpp"
#include "../structs/PacketHeader.hpp"
#include "../types/BodyLen.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = eobi_header::parse(buffer);

    switch (header->template_id.get().value()) {
        case template_id::enum_type::heartbeat_message:
            handler.on_message(*heartbeat_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::product_summary_message:
            handler.on_message(*product_summary_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::snapshot_order_message:
            handler.on_message(*snapshot_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::instrument_summary_message:
            handler.on_message(*instrument_summary_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::auction_best_bid_offer_message:
            handler.on_message(*auction_best_bid_offer_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::auction_clearing_price_message:
            handler.on_message(*auction_clearing_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::top_of_book_message:
            handler.on_message(*top_of_book_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_add_message:
            handler.on_message(*order_add_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_modify_message:
            handler.on_message(*order_modify_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_modify_same_priority_message:
            handler.on_message(*order_modify_same_priority_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_delete_message:
            handler.on_message(*order_delete_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::order_mass_delete_message:
            handler.on_message(*order_mass_delete_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::partial_order_execution_message:
            handler.on_message(*partial_order_execution_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::full_order_execution_message:
            handler.on_message(*full_order_execution_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::trade_reversal_message:
            handler.on_message(*trade_reversal_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::execution_summary_message:
            handler.on_message(*execution_summary_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::instrument_info_message:
            handler.on_message(*instrument_info_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::lpp_range_message:
            handler.on_message(*lpp_range_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::product_state_change_message:
            handler.on_message(*product_state_change_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::instrument_state_change_message:
            handler.on_message(*instrument_state_change_message::parse(buffer), packet_receive_time, transport);
            break;
        case template_id::enum_type::add_complex_instrument_message:
            handler.on_message(*add_complex_instrument_message::parse(buffer), packet_receive_time, transport);
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
