#pragma once

#include <cstdint>
#include <cstddef>

#include "Definitions.hpp"
#include "../structs/MessageHeader.hpp"
#include "../types/MessageLength.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// Template-based message dispatch
// Handler must implement on_message() for each message type

template<typename Handler>
void dispatch(Handler& handler, const std::byte* buffer, std::size_t length) {
    (void)length;
    const auto* header = message_header::parse(buffer + sizeof(sbe_binaryentrypoint::message_length) + sizeof(sbe_binaryentrypoint::encoding_type));

    switch (header->template_id.get().value()) {
        case template_id::enum_type::negotiate_message:
            handler.on_message(*negotiate_message::parse(buffer));
            break;
        case template_id::enum_type::negotiate_response_message:
            handler.on_message(*negotiate_response_message::parse(buffer));
            break;
        case template_id::enum_type::negotiate_reject_message:
            handler.on_message(*negotiate_reject_message::parse(buffer));
            break;
        case template_id::enum_type::establish_message:
            handler.on_message(*establish_message::parse(buffer));
            break;
        case template_id::enum_type::establish_ack_message:
            handler.on_message(*establish_ack_message::parse(buffer));
            break;
        case template_id::enum_type::establish_reject_message:
            handler.on_message(*establish_reject_message::parse(buffer));
            break;
        case template_id::enum_type::terminate_message:
            handler.on_message(*terminate_message::parse(buffer));
            break;
        case template_id::enum_type::not_applied_message:
            handler.on_message(*not_applied_message::parse(buffer));
            break;
        case template_id::enum_type::sequence_message:
            handler.on_message(*sequence_message::parse(buffer));
            break;
        case template_id::enum_type::retransmit_request_message:
            handler.on_message(*retransmit_request_message::parse(buffer));
            break;
        case template_id::enum_type::retransmission_message:
            handler.on_message(*retransmission_message::parse(buffer));
            break;
        case template_id::enum_type::retransmit_reject_message:
            handler.on_message(*retransmit_reject_message::parse(buffer));
            break;
        case template_id::enum_type::simple_new_order_message:
            handler.on_message(*simple_new_order_message::parse(buffer));
            break;
        case template_id::enum_type::simple_modify_order_message:
            handler.on_message(*simple_modify_order_message::parse(buffer));
            break;
        case template_id::enum_type::new_order_single_message:
            handler.on_message(*new_order_single_message::parse(buffer));
            break;
        case template_id::enum_type::order_cancel_replace_request_message:
            handler.on_message(*order_cancel_replace_request_message::parse(buffer));
            break;
        case template_id::enum_type::order_cancel_request_message:
            handler.on_message(*order_cancel_request_message::parse(buffer));
            break;
        case template_id::enum_type::new_order_cross_message:
            handler.on_message(*new_order_cross_message::parse(buffer));
            break;
        case template_id::enum_type::execution_report_new_message:
            handler.on_message(*execution_report_new_message::parse(buffer));
            break;
        case template_id::enum_type::execution_report_modify_message:
            handler.on_message(*execution_report_modify_message::parse(buffer));
            break;
        case template_id::enum_type::execution_report_cancel_message:
            handler.on_message(*execution_report_cancel_message::parse(buffer));
            break;
        case template_id::enum_type::execution_report_trade_message:
            handler.on_message(*execution_report_trade_message::parse(buffer));
            break;
        case template_id::enum_type::execution_report_reject_message:
            handler.on_message(*execution_report_reject_message::parse(buffer));
            break;
        case template_id::enum_type::execution_report_forward_message:
            handler.on_message(*execution_report_forward_message::parse(buffer));
            break;
        case template_id::enum_type::business_message_reject_message:
            handler.on_message(*business_message_reject_message::parse(buffer));
            break;
        case template_id::enum_type::security_definition_request_message:
            handler.on_message(*security_definition_request_message::parse(buffer));
            break;
        case template_id::enum_type::security_definition_response_message:
            handler.on_message(*security_definition_response_message::parse(buffer));
            break;
        case template_id::enum_type::quote_request_message:
            handler.on_message(*quote_request_message::parse(buffer));
            break;
        case template_id::enum_type::quote_status_report_message:
            handler.on_message(*quote_status_report_message::parse(buffer));
            break;
        case template_id::enum_type::quote_message:
            handler.on_message(*quote_message::parse(buffer));
            break;
        case template_id::enum_type::quote_cancel_message:
            handler.on_message(*quote_cancel_message::parse(buffer));
            break;
        case template_id::enum_type::quote_request_reject_message:
            handler.on_message(*quote_request_reject_message::parse(buffer));
            break;
        case template_id::enum_type::position_maintenance_cancel_request_message:
            handler.on_message(*position_maintenance_cancel_request_message::parse(buffer));
            break;
        case template_id::enum_type::position_maintenance_request_message:
            handler.on_message(*position_maintenance_request_message::parse(buffer));
            break;
        case template_id::enum_type::position_maintenance_report_message:
            handler.on_message(*position_maintenance_report_message::parse(buffer));
            break;
        case template_id::enum_type::allocation_instruction_message:
            handler.on_message(*allocation_instruction_message::parse(buffer));
            break;
        case template_id::enum_type::allocation_report_message:
            handler.on_message(*allocation_report_message::parse(buffer));
            break;
        case template_id::enum_type::order_mass_action_request_message:
            handler.on_message(*order_mass_action_request_message::parse(buffer));
            break;
        case template_id::enum_type::order_mass_action_report_message:
            handler.on_message(*order_mass_action_report_message::parse(buffer));
            break;
        default:
            // a code none of the messages answer to: the handler is told when it wants to be
            if constexpr (requires { handler.on_unknown(buffer, length); }) {
                handler.on_unknown(buffer, length);
            }
            break;
    }
}

}
