#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// ref_msg_type
struct ref_msg_type {

    enum class enum_type : std::uint8_t {
        negotiate = 0,
        negotiate_response = 1,
        negotiate_reject = 2,
        establish = 3,
        establish_ack = 4,
        establish_reject = 5,
        terminate = 6,
        not_applied = 9,
        retransmit_request = 10,
        retransmission = 11,
        retransmit_reject = 12,
        sequence = 13,
        business_message_reject = 14,
        simple_new_order = 15,
        simple_modify_order = 16,
        new_order_single = 17,
        order_cancel_replace_request = 18,
        order_cancel_request = 19,
        new_order_cross = 20,
        execution_report_new = 21,
        execution_report_modify = 22,
        execution_report_cancel = 23,
        execution_report_trade = 24,
        execution_report_reject = 25,
        execution_report_forward = 26,
        security_definition_request = 27,
        security_definition_response = 28,
        order_mass_action_request = 29,
        order_mass_action_report = 30,
        quote_request = 31,
        quote_status_report = 32,
        quote = 33,
        quote_cancel = 34,
        quote_request_reject = 35,
        position_maintenance_cancel_request = 36,
        position_maintenance_request = 37,
        position_maintenance_report = 38,
        allocation_instruction = 39,
        allocation_report = 40
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 39> from_string_map = {{
        {"Allocation Instruction", enum_type::allocation_instruction},
        {"Allocation Report", enum_type::allocation_report},
        {"Business Message Reject", enum_type::business_message_reject},
        {"Establish", enum_type::establish},
        {"Establish Ack", enum_type::establish_ack},
        {"Establish Reject", enum_type::establish_reject},
        {"Execution Report Cancel", enum_type::execution_report_cancel},
        {"Execution Report Forward", enum_type::execution_report_forward},
        {"Execution Report Modify", enum_type::execution_report_modify},
        {"Execution Report New", enum_type::execution_report_new},
        {"Execution Report Reject", enum_type::execution_report_reject},
        {"Execution Report Trade", enum_type::execution_report_trade},
        {"Negotiate", enum_type::negotiate},
        {"Negotiate Reject", enum_type::negotiate_reject},
        {"Negotiate Response", enum_type::negotiate_response},
        {"New Order Cross", enum_type::new_order_cross},
        {"New Order Single", enum_type::new_order_single},
        {"Not Applied", enum_type::not_applied},
        {"Order Cancel Replace Request", enum_type::order_cancel_replace_request},
        {"Order Cancel Request", enum_type::order_cancel_request},
        {"Order Mass Action Report", enum_type::order_mass_action_report},
        {"Order Mass Action Request", enum_type::order_mass_action_request},
        {"Position Maintenance Cancel Request", enum_type::position_maintenance_cancel_request},
        {"Position Maintenance Report", enum_type::position_maintenance_report},
        {"Position Maintenance Request", enum_type::position_maintenance_request},
        {"Quote", enum_type::quote},
        {"Quote Cancel", enum_type::quote_cancel},
        {"Quote Request", enum_type::quote_request},
        {"Quote Request Reject", enum_type::quote_request_reject},
        {"Quote Status Report", enum_type::quote_status_report},
        {"Retransmission", enum_type::retransmission},
        {"Retransmit Reject", enum_type::retransmit_reject},
        {"Retransmit Request", enum_type::retransmit_request},
        {"Security Definition Request", enum_type::security_definition_request},
        {"Security Definition Response", enum_type::security_definition_response},
        {"Sequence", enum_type::sequence},
        {"Simple Modify Order", enum_type::simple_modify_order},
        {"Simple New Order", enum_type::simple_new_order},
        {"Terminate", enum_type::terminate}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::negotiate: return "Negotiate";
            case enum_type::negotiate_response: return "Negotiate Response";
            case enum_type::negotiate_reject: return "Negotiate Reject";
            case enum_type::establish: return "Establish";
            case enum_type::establish_ack: return "Establish Ack";
            case enum_type::establish_reject: return "Establish Reject";
            case enum_type::terminate: return "Terminate";
            case enum_type::not_applied: return "Not Applied";
            case enum_type::retransmit_request: return "Retransmit Request";
            case enum_type::retransmission: return "Retransmission";
            case enum_type::retransmit_reject: return "Retransmit Reject";
            case enum_type::sequence: return "Sequence";
            case enum_type::business_message_reject: return "Business Message Reject";
            case enum_type::simple_new_order: return "Simple New Order";
            case enum_type::simple_modify_order: return "Simple Modify Order";
            case enum_type::new_order_single: return "New Order Single";
            case enum_type::order_cancel_replace_request: return "Order Cancel Replace Request";
            case enum_type::order_cancel_request: return "Order Cancel Request";
            case enum_type::new_order_cross: return "New Order Cross";
            case enum_type::execution_report_new: return "Execution Report New";
            case enum_type::execution_report_modify: return "Execution Report Modify";
            case enum_type::execution_report_cancel: return "Execution Report Cancel";
            case enum_type::execution_report_trade: return "Execution Report Trade";
            case enum_type::execution_report_reject: return "Execution Report Reject";
            case enum_type::execution_report_forward: return "Execution Report Forward";
            case enum_type::security_definition_request: return "Security Definition Request";
            case enum_type::security_definition_response: return "Security Definition Response";
            case enum_type::order_mass_action_request: return "Order Mass Action Request";
            case enum_type::order_mass_action_report: return "Order Mass Action Report";
            case enum_type::quote_request: return "Quote Request";
            case enum_type::quote_status_report: return "Quote Status Report";
            case enum_type::quote: return "Quote";
            case enum_type::quote_cancel: return "Quote Cancel";
            case enum_type::quote_request_reject: return "Quote Request Reject";
            case enum_type::position_maintenance_cancel_request: return "Position Maintenance Cancel Request";
            case enum_type::position_maintenance_request: return "Position Maintenance Request";
            case enum_type::position_maintenance_report: return "Position Maintenance Report";
            case enum_type::allocation_instruction: return "Allocation Instruction";
            case enum_type::allocation_report: return "Allocation Report";
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

    static constexpr const char* name = "ref_msg_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<ref_msg_type::enum_type>;
    using storage_type = result_type;

    constexpr ref_msg_type()
     : value{ enum_type{} } {}

    constexpr ref_msg_type(enum_type v)
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
            set(enum_type::allocation_report);
    }

  protected:
    enum_type value;
};
}
