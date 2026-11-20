// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: messages/dispatch.hpp
#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/BodyHeader.hpp"
#include "../structs/FrameHeader.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const frame_header& transport) {
    (void)length;
    const auto* header = body_header::parse(buffer);

    switch (header->msg_type.get().value()) {
        case msg_type::enum_type::heartbeat:
            handler.on_message(*heartbeat_body::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::symbol_status_message:
            handler.on_message(*symbol_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::order_book_message:
            handler.on_message(*order_book_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::order_book_terms_message:
            handler.on_message(*order_book_terms_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::assign_cop_orders_message:
            handler.on_message(*assign_cop_orders_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::assign_cop_no_orders_message:
            handler.on_message(*assign_cop_no_orders_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::assign_limit_message:
            handler.on_message(*assign_limit_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::market_state_update_message:
            handler.on_message(*market_state_update_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::moc_imbalance_message:
            handler.on_message(*moc_imbalance_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::order_booked_message:
            handler.on_message(*order_booked_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::order_booked_terms_message:
            handler.on_message(*order_booked_terms_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::order_cancelled_message:
            handler.on_message(*order_cancelled_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::order_cancelled_terms_message:
            handler.on_message(*order_cancelled_terms_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::order_price_time_assigned_message:
            handler.on_message(*order_price_time_assigned_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::order_price_time_assigned_terms_message:
            handler.on_message(*order_price_time_assigned_terms_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::stock_status_message:
            handler.on_message(*stock_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::trade_report_message:
            handler.on_message(*trade_report_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::trade_report_terms_message:
            handler.on_message(*trade_report_terms_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::trade_cancelled_message:
            handler.on_message(*trade_cancelled_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::trade_cancelled_terms_message:
            handler.on_message(*trade_cancelled_terms_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::trade_correction_message:
            handler.on_message(*trade_correction_message::parse(buffer), packet_receive_time, transport);
            break;
        case msg_type::enum_type::trade_correction_terms_message:
            handler.on_message(*trade_correction_terms_message::parse(buffer), packet_receive_time, transport);
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
