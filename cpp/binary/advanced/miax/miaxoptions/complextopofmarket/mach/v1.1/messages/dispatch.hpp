// Miax.MiaxOptions.ComplexTopOfMarket.Mach.v1.1: messages/dispatch.hpp
#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/ApplicationMessage.hpp"
#include "../types/PacketLength.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (system_time_message::parse(buffer)->header.packet_type.get().value()) {
        case packet_type::enum_type::application_message: {
            switch (system_time_message::parse(buffer)->message_type.get().value()) {
                case message_type::enum_type::system_time_message:
                    handler.on_message(*system_time_message::parse(buffer));
                    break;
                case message_type::enum_type::series_update:
                    handler.on_message(*series_update::parse(buffer));
                    break;
                case message_type::enum_type::complex_strategy_definition_message:
                    handler.on_message(*complex_strategy_definition_message::parse(buffer));
                    break;
                case message_type::enum_type::system_state_message:
                    handler.on_message(*system_state_message::parse(buffer));
                    break;
                case message_type::enum_type::compact_complex_top_of_market_bid_message:
                    handler.on_message(*compact_complex_top_of_market_bid_message::parse(buffer));
                    break;
                case message_type::enum_type::compact_complex_top_of_market_offer_message:
                    handler.on_message(*compact_complex_top_of_market_offer_message::parse(buffer));
                    break;
                case message_type::enum_type::wide_complex_top_of_market_bid_message:
                    handler.on_message(*wide_complex_top_of_market_bid_message::parse(buffer));
                    break;
                case message_type::enum_type::wide_complex_top_of_market_offer_message:
                    handler.on_message(*wide_complex_top_of_market_offer_message::parse(buffer));
                    break;
                case message_type::enum_type::compact_complex_double_sided_top_of_market_message:
                    handler.on_message(*compact_complex_double_sided_top_of_market_message::parse(buffer));
                    break;
                case message_type::enum_type::wide_complex_double_sided_top_of_market_message:
                    handler.on_message(*wide_complex_double_sided_top_of_market_message::parse(buffer));
                    break;
                case message_type::enum_type::strategy_trade_message:
                    handler.on_message(*strategy_trade_message::parse(buffer));
                    break;
                case message_type::enum_type::underlying_trading_status_message:
                    handler.on_message(*underlying_trading_status_message::parse(buffer));
                    break;
                default:
                    // Unknown Message Type
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
