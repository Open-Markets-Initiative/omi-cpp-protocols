#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/AdministrativeMessage.hpp"
#include "../structs/BlockHeader.hpp"
#include "../types/MessageLength.hpp"

namespace siac::cts::output::cta::v1_91 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const block_header& transport) {
    (void)length;

    switch (start_of_end_of_day_message::parse(buffer)->message_category.get().value()) {
        case message_category::enum_type::administrative: {
            switch (start_of_end_of_day_message::parse(buffer)->administrative_message_type.get().value()) {
                case administrative_message_type::enum_type::start_of_end_of_day_message:
                    handler.on_message(*start_of_end_of_day_message::parse(buffer), packet_receive_time, transport);
                    break;
                case administrative_message_type::enum_type::end_of_end_of_day_message:
                    handler.on_message(*end_of_end_of_day_message::parse(buffer), packet_receive_time, transport);
                    break;
                case administrative_message_type::enum_type::start_of_start_of_day_message:
                    handler.on_message(*start_of_start_of_day_message::parse(buffer), packet_receive_time, transport);
                    break;
                case administrative_message_type::enum_type::end_of_start_of_day_message:
                    handler.on_message(*end_of_start_of_day_message::parse(buffer), packet_receive_time, transport);
                    break;
                case administrative_message_type::enum_type::administrative_unformatted_message:
                    handler.on_message(*administrative_unformatted_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Administrative Message Type
                    break;
            }
            break;
        }
        case message_category::enum_type::control: {
            switch (start_of_day_message::parse(buffer)->control_message_type.get().value()) {
                case control_message_type::enum_type::start_of_day_message:
                    handler.on_message(*start_of_day_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::reset_block_sequence_number_message:
                    handler.on_message(*reset_block_sequence_number_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::start_of_test_cycle_message:
                    handler.on_message(*start_of_test_cycle_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::end_of_test_cycle_message:
                    handler.on_message(*end_of_test_cycle_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::disaster_recovery_data_center_activation_message:
                    handler.on_message(*disaster_recovery_data_center_activation_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::line_integrity_message:
                    handler.on_message(*line_integrity_message::parse(buffer), packet_receive_time, transport);
                    break;
                case control_message_type::enum_type::end_of_day_message:
                    handler.on_message(*end_of_day_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Control Message Type
                    break;
            }
            break;
        }
        case message_category::enum_type::indices: {
            switch (index_message::parse(buffer)->indices_message_type.get().value()) {
                case indices_message_type::enum_type::index_message:
                    handler.on_message(*index_message::parse(buffer), packet_receive_time, transport);
                    break;
                case indices_message_type::enum_type::bid_and_offer_index_message:
                    handler.on_message(*bid_and_offer_index_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Indices Message Type
                    break;
            }
            break;
        }
        case message_category::enum_type::market_status: {
            switch (market_wide_circuit_breaker_decline_level_status_message::parse(buffer)->market_status_message_type.get().value()) {
                case market_status_message_type::enum_type::market_wide_circuit_breaker_decline_level_status_message:
                    handler.on_message(*market_wide_circuit_breaker_decline_level_status_message::parse(buffer), packet_receive_time, transport);
                    break;
                case market_status_message_type::enum_type::market_wide_circuit_breaker_status_message:
                    handler.on_message(*market_wide_circuit_breaker_status_message::parse(buffer), packet_receive_time, transport);
                    break;
                case market_status_message_type::enum_type::approximate_adjusted_volume_market_center_message:
                    handler.on_message(*approximate_adjusted_volume_market_center_message::parse(buffer), packet_receive_time, transport);
                    break;
                case market_status_message_type::enum_type::approximate_trades_and_total_dollar_value_message:
                    handler.on_message(*approximate_trades_and_total_dollar_value_message::parse(buffer), packet_receive_time, transport);
                    break;
                case market_status_message_type::enum_type::crossing_session_summary_message:
                    handler.on_message(*crossing_session_summary_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Market Status Message Type
                    break;
            }
            break;
        }
        case message_category::enum_type::prior_day: {
            switch (prior_day_trade_correction_message::parse(buffer)->prior_day_message_type.get().value()) {
                case prior_day_message_type::enum_type::prior_day_trade_correction_message:
                    handler.on_message(*prior_day_trade_correction_message::parse(buffer), packet_receive_time, transport);
                    break;
                case prior_day_message_type::enum_type::prior_day_trade_message:
                    handler.on_message(*prior_day_trade_message::parse(buffer), packet_receive_time, transport);
                    break;
                case prior_day_message_type::enum_type::prior_day_trade_cancel_error_message:
                    handler.on_message(*prior_day_trade_cancel_error_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Prior Day Message Type
                    break;
            }
            break;
        }
        case message_category::enum_type::summary: {
            switch (consolidated_start_of_day_summary_message::parse(buffer)->summary_message_type.get().value()) {
                case summary_message_type::enum_type::consolidated_start_of_day_summary_message:
                    handler.on_message(*consolidated_start_of_day_summary_message::parse(buffer), packet_receive_time, transport);
                    break;
                case summary_message_type::enum_type::participant_start_of_day_summary_message:
                    handler.on_message(*participant_start_of_day_summary_message::parse(buffer), packet_receive_time, transport);
                    break;
                case summary_message_type::enum_type::consolidated_end_of_day_summary_message:
                    handler.on_message(*consolidated_end_of_day_summary_message::parse(buffer), packet_receive_time, transport);
                    break;
                case summary_message_type::enum_type::participant_end_of_day_summary_message:
                    handler.on_message(*participant_end_of_day_summary_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Summary Message Type
                    break;
            }
            break;
        }
        case message_category::enum_type::trade: {
            switch (auction_status_message::parse(buffer)->trade_message_type.get().value()) {
                case trade_message_type::enum_type::auction_status_message:
                    handler.on_message(*auction_status_message::parse(buffer), packet_receive_time, transport);
                    break;
                case trade_message_type::enum_type::trade_correction_message:
                    handler.on_message(*trade_correction_message::parse(buffer), packet_receive_time, transport);
                    break;
                case trade_message_type::enum_type::long_trade_message:
                    handler.on_message(*long_trade_message::parse(buffer), packet_receive_time, transport);
                    break;
                case trade_message_type::enum_type::trading_status_message:
                    handler.on_message(*trading_status_message::parse(buffer), packet_receive_time, transport);
                    break;
                case trade_message_type::enum_type::short_trade_message:
                    handler.on_message(*short_trade_message::parse(buffer), packet_receive_time, transport);
                    break;
                case trade_message_type::enum_type::trade_cancel_error_message:
                    handler.on_message(*trade_cancel_error_message::parse(buffer), packet_receive_time, transport);
                    break;
                default:
                    // Unknown Trade Message Type
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
