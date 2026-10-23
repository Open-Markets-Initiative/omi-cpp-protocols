#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/AdministrativeMessage.hpp"
#include "../structs/BlockHeader.hpp"
#include "../types/MessageLength.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const block_header& transport) {
    (void)length;

    switch (symbol_reference_data_message::parse(buffer)->message_category.get().value()) {
        case message_category::enum_type::administrative: {
            switch (symbol_reference_data_message::parse(buffer)->administrative_message_type.get().value()) {
                case administrative_message_type::enum_type::symbol_reference_data:
                    handler.on_message(*symbol_reference_data_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Administrative Message Type
                    break;
            }
            break;
        }
        case message_category::enum_type::control: {
            switch (start_of_day_message::parse(buffer)->control_message_type.get().value()) {
                case control_message_type::enum_type::start_of_day:
                    handler.on_message(*start_of_day_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::finra_close:
                    handler.on_message(*finra_close_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::reset_block_sequence_number:
                    handler.on_message(*reset_block_sequence_number_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::finra_open:
                    handler.on_message(*finra_open_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::disaster_recovery_data_center_activation:
                    handler.on_message(*disaster_recovery_data_center_activation_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::line_integrity:
                    handler.on_message(*line_integrity_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::end_of_day:
                    handler.on_message(*end_of_day_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Control Message Type
                    break;
            }
            break;
        }
        case message_category::enum_type::market_status: {
            switch (market_wide_circuit_breaker_decline_level_status_message::parse(buffer)->market_status_message_type.get().value()) {
                case market_status_message_type::enum_type::market_wide_circuit_breaker_decline_level_status:
                    handler.on_message(*market_wide_circuit_breaker_decline_level_status_message::parse(buffer), packet_receive_time, transport);
                    break;
                case market_status_message_type::enum_type::market_wide_circuit_breaker_status:
                    handler.on_message(*market_wide_circuit_breaker_status_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Market Status Message Type
                    break;
            }
            break;
        }
        case message_category::enum_type::quote: {
            switch (auction_status_message::parse(buffer)->quote_message_type.get().value()) {
                case quote_message_type::enum_type::auction_status:
                    handler.on_message(*auction_status_message::parse(buffer), packet_receive_time, transport);
                    break;
                case quote_message_type::enum_type::long_quote:
                    handler.on_message(*long_quote_message::parse(buffer), packet_receive_time, transport);
                    break;
                case quote_message_type::enum_type::short_quote:
                    handler.on_message(*short_quote_message::parse(buffer), packet_receive_time, transport);
                    break;
                case quote_message_type::enum_type::special_long_quote:
                    handler.on_message(*special_long_quote_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Quote Message Type
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

}
