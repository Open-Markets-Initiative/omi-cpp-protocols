// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: messages/dispatch.hpp
#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/ApplicationMessage.hpp"
#include "../types/PacketLength.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;

    switch (simple_instrument_definition_message::parse(buffer)->header.packet_type.get().value()) {
        case packet_type::enum_type::application_message: {
            switch (simple_instrument_definition_message::parse(buffer)->message_type.get().value()) {
                case message_type::enum_type::simple_instrument_definition_message:
                    handler.on_message(*simple_instrument_definition_message::parse(buffer));
                    break;
                case message_type::enum_type::complex_instrument_definition_message:
                    handler.on_message(*complex_instrument_definition_message::parse(buffer));
                    break;
                case message_type::enum_type::system_state_message:
                    handler.on_message(*system_state_message::parse(buffer));
                    break;
                case message_type::enum_type::instrument_trading_status_notification_message:
                    handler.on_message(*instrument_trading_status_notification_message::parse(buffer));
                    break;
                case message_type::enum_type::best_bid_and_offer_message:
                    handler.on_message(*best_bid_and_offer_message::parse(buffer));
                    break;
                case message_type::enum_type::last_sale_message:
                    handler.on_message(*last_sale_message::parse(buffer));
                    break;
                case message_type::enum_type::trade_cancel_message:
                    handler.on_message(*trade_cancel_message::parse(buffer));
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
