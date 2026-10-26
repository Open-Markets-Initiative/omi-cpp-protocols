#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::seconds_message:
            handler.on_message(*seconds_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::end_of_business_trade_date_message:
            handler.on_message(*end_of_business_trade_date_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::future_symbol_directory_message:
            handler.on_message(*future_symbol_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_symbol_directory_message:
            handler.on_message(*options_symbol_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::combination_symbol_directory_message:
            handler.on_message(*combination_symbol_directory_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::bundles_symbol_directory:
            handler.on_message(*bundles_symbol_directory::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_book_state_message:
            handler.on_message(*order_book_state_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_message:
            handler.on_message(*add_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_volume_cancelled_message:
            handler.on_message(*order_volume_cancelled_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_deleted_message:
            handler.on_message(*order_deleted_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::auction_order_executed_message:
            handler.on_message(*auction_order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::combination_order_executed_message:
            handler.on_message(*combination_order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::implied_order_added_message:
            handler.on_message(*implied_order_added_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::implied_order_replaced_message:
            handler.on_message(*implied_order_replaced_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::implied_order_deleted_message:
            handler.on_message(*implied_order_deleted_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_executed_message:
            handler.on_message(*trade_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::combination_trade_executed_message:
            handler.on_message(*combination_trade_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::trade_cancellation_message:
            handler.on_message(*trade_cancellation_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::equilibrium_price_message:
            handler.on_message(*equilibrium_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::open_high_low_last_trade_adjustment_message:
            handler.on_message(*open_high_low_last_trade_adjustment_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::market_settlement_message:
            handler.on_message(*market_settlement_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::text_message:
            handler.on_message(*text_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::request_for_quote_message:
            handler.on_message(*request_for_quote_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::anomalous_order_threshold_publish_message:
            handler.on_message(*anomalous_order_threshold_publish_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::volume_and_open_interest_message:
            handler.on_message(*volume_and_open_interest_message::parse(buffer), packet_receive_time, transport);
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
