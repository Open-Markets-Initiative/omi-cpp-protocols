#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// exec_restatement_reason
struct exec_restatement_reason {

    enum class enum_type : std::uint8_t {
        market_option = 8,
        cancel_on_hard_disconnection = 100,
        cancel_on_terminate = 101,
        cancel_on_disconnect_and_terminate = 102,
        self_trading_prevention = 103,
        cancel_from_firmsoft = 105,
        cancel_resting_order_on_self_trade = 107,
        market_maker_protection = 200,
        risk_management_cancellation = 201,
        order_mass_action_from_client_request = 202,
        cancel_order_due_to_operational_error = 203,
        order_cancelled_due_to_operational_error = 204,
        cancel_order_firmsoft_due_to_operational_error = 205,
        order_cancelled_firmsoft_due_to_operational_error = 206,
        mass_cancel_order_due_to_operational_error_request = 207,
        mass_cancel_order_due_to_operational_error_effective = 208,
        cancel_on_midpoint_broker_only_removal = 209,
        no_value = 0
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 18> from_string_map = {{
        {"Cancel From Firmsoft", enum_type::cancel_from_firmsoft},
        {"Cancel On Disconnect And Terminate", enum_type::cancel_on_disconnect_and_terminate},
        {"Cancel On Hard Disconnection", enum_type::cancel_on_hard_disconnection},
        {"Cancel On Midpoint Broker Only Removal", enum_type::cancel_on_midpoint_broker_only_removal},
        {"Cancel On Terminate", enum_type::cancel_on_terminate},
        {"Cancel Order Due To Operational Error", enum_type::cancel_order_due_to_operational_error},
        {"Cancel Order Firmsoft Due To Operational Error", enum_type::cancel_order_firmsoft_due_to_operational_error},
        {"Cancel Resting Order On Self Trade", enum_type::cancel_resting_order_on_self_trade},
        {"Market Maker Protection", enum_type::market_maker_protection},
        {"Market Option", enum_type::market_option},
        {"Mass Cancel Order Due To Operational Error Effective", enum_type::mass_cancel_order_due_to_operational_error_effective},
        {"Mass Cancel Order Due To Operational Error Request", enum_type::mass_cancel_order_due_to_operational_error_request},
        {"No Value", enum_type::no_value},
        {"Order Cancelled Due To Operational Error", enum_type::order_cancelled_due_to_operational_error},
        {"Order Cancelled Firmsoft Due To Operational Error", enum_type::order_cancelled_firmsoft_due_to_operational_error},
        {"Order Mass Action From Client Request", enum_type::order_mass_action_from_client_request},
        {"Risk Management Cancellation", enum_type::risk_management_cancellation},
        {"Self Trading Prevention", enum_type::self_trading_prevention}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::market_option: return "Market Option";
            case enum_type::cancel_on_hard_disconnection: return "Cancel On Hard Disconnection";
            case enum_type::cancel_on_terminate: return "Cancel On Terminate";
            case enum_type::cancel_on_disconnect_and_terminate: return "Cancel On Disconnect And Terminate";
            case enum_type::self_trading_prevention: return "Self Trading Prevention";
            case enum_type::cancel_from_firmsoft: return "Cancel From Firmsoft";
            case enum_type::cancel_resting_order_on_self_trade: return "Cancel Resting Order On Self Trade";
            case enum_type::market_maker_protection: return "Market Maker Protection";
            case enum_type::risk_management_cancellation: return "Risk Management Cancellation";
            case enum_type::order_mass_action_from_client_request: return "Order Mass Action From Client Request";
            case enum_type::cancel_order_due_to_operational_error: return "Cancel Order Due To Operational Error";
            case enum_type::order_cancelled_due_to_operational_error: return "Order Cancelled Due To Operational Error";
            case enum_type::cancel_order_firmsoft_due_to_operational_error: return "Cancel Order Firmsoft Due To Operational Error";
            case enum_type::order_cancelled_firmsoft_due_to_operational_error: return "Order Cancelled Firmsoft Due To Operational Error";
            case enum_type::mass_cancel_order_due_to_operational_error_request: return "Mass Cancel Order Due To Operational Error Request";
            case enum_type::mass_cancel_order_due_to_operational_error_effective: return "Mass Cancel Order Due To Operational Error Effective";
            case enum_type::cancel_on_midpoint_broker_only_removal: return "Cancel On Midpoint Broker Only Removal";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "exec_restatement_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<exec_restatement_reason::enum_type>;
    using storage_type = result_type;

    constexpr exec_restatement_reason()
     : value{ enum_type{} } {}

    constexpr exec_restatement_reason(enum_type v)
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
            set(static_cast<enum_type>(0));
    }

  protected:
    enum_type value;
};
}
