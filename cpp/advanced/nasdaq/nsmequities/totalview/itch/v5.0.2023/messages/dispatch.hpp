#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

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
        case message_type::enum_type::reg_sho_short_sale_price_test_restricted_indicator_message:
            handler.on_message(*reg_sho_short_sale_price_test_restricted_indicator_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::market_participant_position_message:
            handler.on_message(*market_participant_position_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::mwcb_decline_level_message:
            handler.on_message(*mwcb_decline_level_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::mwcb_status_level_message:
            handler.on_message(*mwcb_status_level_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::ipo_quoting_period_update:
            handler.on_message(*ipo_quoting_period_update::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::luld_auction_collar_message:
            handler.on_message(*luld_auction_collar_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::operational_halt_message:
            handler.on_message(*operational_halt_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_no_mpid_attribution_message:
            handler.on_message(*add_order_no_mpid_attribution_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::add_order_with_mpid_attribution_message:
            handler.on_message(*add_order_with_mpid_attribution_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_message:
            handler.on_message(*order_executed_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_executed_with_price_message:
            handler.on_message(*order_executed_with_price_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_cancel_message:
            handler.on_message(*order_cancel_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_delete_message:
            handler.on_message(*order_delete_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::order_replace_message:
            handler.on_message(*order_replace_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::non_cross_trade_message:
            handler.on_message(*non_cross_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::cross_trade_message:
            handler.on_message(*cross_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::broken_trade_message:
            handler.on_message(*broken_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::net_order_imbalance_indicator_message:
            handler.on_message(*net_order_imbalance_indicator_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::retail_price_improvement_indicator_message:
            handler.on_message(*retail_price_improvement_indicator_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::direct_listing_with_capital_raise_price_discovery_message:
            handler.on_message(*direct_listing_with_capital_raise_price_discovery_message::parse(buffer), packet_receive_time, transport);
            break;
        default:
            // Unknown message type - handler should implement on_unknown if needed
            break;
    }
}

// Dispatch for the Server Packet tree
template<typename Handler>
void dispatch_server_packet(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (login_accepted_packet::parse(buffer)->header.server_packet_type.get().value()) {
        case server_packet_type::enum_type::login_accepted_packet:
            handler.on_message(*login_accepted_packet::parse(buffer));
            break;
        case server_packet_type::enum_type::login_rejected_packet:
            handler.on_message(*login_rejected_packet::parse(buffer));
            break;
        case server_packet_type::enum_type::sequenced_data_packet:
            handler.on_message(*sequenced_data_packet::parse(buffer));
            break;
        default:
            // Unknown message type - handler should implement on_unknown if needed
            break;
    }
}

// Dispatch for the Client Packet tree
template<typename Handler>
void dispatch_client_packet(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (debug_packet::parse(buffer)->header.client_packet_type.get().value()) {
        case client_packet_type::enum_type::debug_packet:
            handler.on_message(*debug_packet::parse(buffer));
            break;
        case client_packet_type::enum_type::login_request_packet:
            handler.on_message(*login_request_packet::parse(buffer));
            break;
        case client_packet_type::enum_type::unsequenced_data_packet:
            handler.on_message(*unsequenced_data_packet::parse(buffer));
            break;
        default:
            // Unknown message type - handler should implement on_unknown if needed
            break;
    }
}

}
