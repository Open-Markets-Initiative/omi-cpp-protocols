#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/ApplicationMessage.hpp"
#include "../structs/MachMessage.hpp"
#include "../types/PacketLength.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const mach_message& transport) {
    (void)length;

    switch (system_time_message::parse(buffer)->packet_type.get().value()) {
        case packet_type::enum_type::application_message: {
            switch (system_time_message::parse(buffer)->message_type.get().value()) {
                case message_type::enum_type::system_time_message:
                    handler.on_message(*system_time_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::simple_series_update_message:
                    handler.on_message(*simple_series_update_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::system_state_message:
                    handler.on_message(*system_state_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::simple_top_of_market_best_bid_or_offer_compact_bid_message:
                    handler.on_message(*simple_top_of_market_best_bid_or_offer_compact_bid_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::simple_top_of_market_best_bid_or_offer_compact_offer_message:
                    handler.on_message(*simple_top_of_market_best_bid_or_offer_compact_offer_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::simple_top_of_market_best_bid_or_offer_wide_bid_message:
                    handler.on_message(*simple_top_of_market_best_bid_or_offer_wide_bid_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::simple_top_of_market_best_bid_or_offer_wide_offer_message:
                    handler.on_message(*simple_top_of_market_best_bid_or_offer_wide_offer_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::simple_double_sided_top_of_market_best_bid_or_offer_compact_message:
                    handler.on_message(*simple_double_sided_top_of_market_best_bid_or_offer_compact_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::simple_double_sided_top_of_market_best_bid_or_offer_wide_message:
                    handler.on_message(*simple_double_sided_top_of_market_best_bid_or_offer_wide_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::last_sale_message:
                    handler.on_message(*last_sale_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::trade_cancel_message:
                    handler.on_message(*trade_cancel_message::parse(buffer), packet_receive_time, transport);
                    break;
                case message_type::enum_type::underlying_trading_status_notification_message:
                    handler.on_message(*underlying_trading_status_notification_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Message Type
                    break;
            }
            break;
        }
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length, packet_receive_time, transport); }) {
                handler.on_unknown(buffer, length, packet_receive_time, transport);
            }
            break;
    }
}

// Dispatch for the Tcp Packet tree
template<typename Handler>
void dispatch_tcp_packet(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (refresh_request_message::parse(buffer)->header.sesm_packet_type.get().value()) {
        case sesm_packet_type::enum_type::unsequenced_data_packet: {
            switch (refresh_request_message::parse(buffer)->unsequenced_message_type.get().value()) {
                case unsequenced_message_type::enum_type::refresh_request_message:
                    handler.on_message(*refresh_request_message::parse(buffer));
                    break;
                case unsequenced_message_type::enum_type::refresh_response_message:
                    handler.on_message(*refresh_response_message::parse(buffer));
                    break;
                case unsequenced_message_type::enum_type::end_of_refresh_notification_message:
                    handler.on_message(*end_of_refresh_notification_message::parse(buffer));
                    break;
                default:
                    // Unknown Unsequenced Message Type
                    break;
            }
            break;
        }
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length); }) {
                handler.on_unknown(buffer, length);
            }
            break;
    }
}

}
