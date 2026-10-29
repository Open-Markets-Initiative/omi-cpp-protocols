#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// template_id
struct template_id {

    enum class enum_type : std::uint16_t {
        negotiate_message = 1,
        negotiate_response_message = 2,
        negotiate_reject_message = 3,
        establish_message = 4,
        establish_ack_message = 5,
        establish_reject_message = 6,
        terminate_message = 7,
        not_applied_message = 8,
        sequence_message = 9,
        retransmit_request_message = 12,
        retransmission_message = 13,
        retransmit_reject_message = 14,
        simple_new_order_message = 100,
        simple_modify_order_message = 101,
        new_order_single_message = 102,
        order_cancel_replace_request_message = 104,
        order_cancel_request_message = 105,
        new_order_cross_message = 106,
        execution_report_new_message = 200,
        execution_report_modify_message = 201,
        execution_report_cancel_message = 202,
        execution_report_trade_message = 203,
        execution_report_reject_message = 204,
        execution_report_forward_message = 205,
        business_message_reject_message = 206,
        security_definition_request_message = 300,
        security_definition_response_message = 301,
        quote_request_message = 401,
        quote_status_report_message = 402,
        quote_message = 403,
        quote_cancel_message = 404,
        quote_request_reject_message = 405,
        position_maintenance_cancel_request_message = 501,
        position_maintenance_request_message = 502,
        position_maintenance_report_message = 503,
        allocation_instruction_message = 601,
        allocation_report_message = 602,
        order_mass_action_request_message = 701,
        order_mass_action_report_message = 702
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 39> from_string_map = {{
        {"Allocation Instruction Message", enum_type::allocation_instruction_message},
        {"Allocation Report Message", enum_type::allocation_report_message},
        {"Business Message Reject Message", enum_type::business_message_reject_message},
        {"Establish Ack Message", enum_type::establish_ack_message},
        {"Establish Message", enum_type::establish_message},
        {"Establish Reject Message", enum_type::establish_reject_message},
        {"Execution Report Cancel Message", enum_type::execution_report_cancel_message},
        {"Execution Report Forward Message", enum_type::execution_report_forward_message},
        {"Execution Report Modify Message", enum_type::execution_report_modify_message},
        {"Execution Report New Message", enum_type::execution_report_new_message},
        {"Execution Report Reject Message", enum_type::execution_report_reject_message},
        {"Execution Report Trade Message", enum_type::execution_report_trade_message},
        {"Negotiate Message", enum_type::negotiate_message},
        {"Negotiate Reject Message", enum_type::negotiate_reject_message},
        {"Negotiate Response Message", enum_type::negotiate_response_message},
        {"New Order Cross Message", enum_type::new_order_cross_message},
        {"New Order Single Message", enum_type::new_order_single_message},
        {"Not Applied Message", enum_type::not_applied_message},
        {"Order Cancel Replace Request Message", enum_type::order_cancel_replace_request_message},
        {"Order Cancel Request Message", enum_type::order_cancel_request_message},
        {"Order Mass Action Report Message", enum_type::order_mass_action_report_message},
        {"Order Mass Action Request Message", enum_type::order_mass_action_request_message},
        {"Position Maintenance Cancel Request Message", enum_type::position_maintenance_cancel_request_message},
        {"Position Maintenance Report Message", enum_type::position_maintenance_report_message},
        {"Position Maintenance Request Message", enum_type::position_maintenance_request_message},
        {"Quote Cancel Message", enum_type::quote_cancel_message},
        {"Quote Message", enum_type::quote_message},
        {"Quote Request Message", enum_type::quote_request_message},
        {"Quote Request Reject Message", enum_type::quote_request_reject_message},
        {"Quote Status Report Message", enum_type::quote_status_report_message},
        {"Retransmission Message", enum_type::retransmission_message},
        {"Retransmit Reject Message", enum_type::retransmit_reject_message},
        {"Retransmit Request Message", enum_type::retransmit_request_message},
        {"Security Definition Request Message", enum_type::security_definition_request_message},
        {"Security Definition Response Message", enum_type::security_definition_response_message},
        {"Sequence Message", enum_type::sequence_message},
        {"Simple Modify Order Message", enum_type::simple_modify_order_message},
        {"Simple New Order Message", enum_type::simple_new_order_message},
        {"Terminate Message", enum_type::terminate_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::negotiate_message: return "Negotiate Message";
            case enum_type::negotiate_response_message: return "Negotiate Response Message";
            case enum_type::negotiate_reject_message: return "Negotiate Reject Message";
            case enum_type::establish_message: return "Establish Message";
            case enum_type::establish_ack_message: return "Establish Ack Message";
            case enum_type::establish_reject_message: return "Establish Reject Message";
            case enum_type::terminate_message: return "Terminate Message";
            case enum_type::not_applied_message: return "Not Applied Message";
            case enum_type::sequence_message: return "Sequence Message";
            case enum_type::retransmit_request_message: return "Retransmit Request Message";
            case enum_type::retransmission_message: return "Retransmission Message";
            case enum_type::retransmit_reject_message: return "Retransmit Reject Message";
            case enum_type::simple_new_order_message: return "Simple New Order Message";
            case enum_type::simple_modify_order_message: return "Simple Modify Order Message";
            case enum_type::new_order_single_message: return "New Order Single Message";
            case enum_type::order_cancel_replace_request_message: return "Order Cancel Replace Request Message";
            case enum_type::order_cancel_request_message: return "Order Cancel Request Message";
            case enum_type::new_order_cross_message: return "New Order Cross Message";
            case enum_type::execution_report_new_message: return "Execution Report New Message";
            case enum_type::execution_report_modify_message: return "Execution Report Modify Message";
            case enum_type::execution_report_cancel_message: return "Execution Report Cancel Message";
            case enum_type::execution_report_trade_message: return "Execution Report Trade Message";
            case enum_type::execution_report_reject_message: return "Execution Report Reject Message";
            case enum_type::execution_report_forward_message: return "Execution Report Forward Message";
            case enum_type::business_message_reject_message: return "Business Message Reject Message";
            case enum_type::security_definition_request_message: return "Security Definition Request Message";
            case enum_type::security_definition_response_message: return "Security Definition Response Message";
            case enum_type::quote_request_message: return "Quote Request Message";
            case enum_type::quote_status_report_message: return "Quote Status Report Message";
            case enum_type::quote_message: return "Quote Message";
            case enum_type::quote_cancel_message: return "Quote Cancel Message";
            case enum_type::quote_request_reject_message: return "Quote Request Reject Message";
            case enum_type::position_maintenance_cancel_request_message: return "Position Maintenance Cancel Request Message";
            case enum_type::position_maintenance_request_message: return "Position Maintenance Request Message";
            case enum_type::position_maintenance_report_message: return "Position Maintenance Report Message";
            case enum_type::allocation_instruction_message: return "Allocation Instruction Message";
            case enum_type::allocation_report_message: return "Allocation Report Message";
            case enum_type::order_mass_action_request_message: return "Order Mass Action Request Message";
            case enum_type::order_mass_action_report_message: return "Order Mass Action Report Message";
            default: return "unknown";
        }
    }

    static constexpr std::optional<enum_type> from_string(std::string_view str) {
        auto it = std::lower_bound(
            from_string_map.begin(),
            from_string_map.end(),
            str,
            [](const auto& pair, std::string_view s) { return pair.first < s; }
        );
        if (it != from_string_map.end() && it->first == str) {
            return it->second;
        }
        return std::nullopt;
    }

    static constexpr const char* name = "template_id";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<template_id::enum_type>;
    using storage_type = result_type;

    constexpr template_id()
     : value{ enum_type{} } {}

    constexpr template_id(enum_type v)
     : value{ v } {}

    [[nodiscard]] constexpr result_type get() const {
        return result_type{value};
    }

    constexpr void set(enum_type v) {
        value = v;
    }

    constexpr void set(result_type value) {
        if (value.has_value())
            set(value.value());
        else
            set(enum_type::order_mass_action_report_message);
    }

  protected:
    enum_type value;
};
}
