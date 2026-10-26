#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../structs/PacketHeader.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length, std::uint64_t packet_receive_time, const packet_header& transport) {
    (void)length;
    const auto* header = message_header::parse(buffer);

    switch (header->message_type.get().value()) {
        case message_type::enum_type::sequence_number_reset_message:
            handler.on_message(*sequence_number_reset_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::source_time_reference_message:
            handler.on_message(*source_time_reference_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::symbol_index_mapping_message:
            handler.on_message(*symbol_index_mapping_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::symbol_clear_message:
            handler.on_message(*symbol_clear_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::security_status_message:
            handler.on_message(*security_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::outright_series_index_mapping_message:
            handler.on_message(*outright_series_index_mapping_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_status_message:
            handler.on_message(*options_status_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::complex_series_index_mapping_message:
            handler.on_message(*complex_series_index_mapping_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::retransmission_request_message:
            handler.on_message(*retransmission_request_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::refresh_header_message:
            handler.on_message(*refresh_header_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::refresh_request_message:
            handler.on_message(*refresh_request_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::symbol_index_mapping_request_message:
            handler.on_message(*symbol_index_mapping_request_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::message_unavailable_message:
            handler.on_message(*message_unavailable_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::request_response_message:
            handler.on_message(*request_response_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::heartbeat_response_message:
            handler.on_message(*heartbeat_response_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_add_order_message:
            handler.on_message(*options_add_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_modify_order_message:
            handler.on_message(*options_modify_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_delete_order_message:
            handler.on_message(*options_delete_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_order_execution_message:
            handler.on_message(*options_order_execution_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_replace_order_message:
            handler.on_message(*options_replace_order_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_imbalance_message:
            handler.on_message(*options_imbalance_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_add_order_refresh_message:
            handler.on_message(*options_add_order_refresh_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_series_rfq_message:
            handler.on_message(*options_series_rfq_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_non_displayed_trade_message:
            handler.on_message(*options_non_displayed_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_cross_trade_message:
            handler.on_message(*options_cross_trade_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_trade_cancel_message:
            handler.on_message(*options_trade_cancel_message::parse(buffer), packet_receive_time, transport);
            break;
        case message_type::enum_type::options_outright_series_summary_message:
            handler.on_message(*options_outright_series_summary_message::parse(buffer), packet_receive_time, transport);
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
