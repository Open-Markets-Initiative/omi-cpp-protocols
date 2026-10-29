#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// order_canceled_reason
struct order_canceled_reason {

    enum class enum_type : char {
        user_requested_cancel = 'U',
        user_logged_off = 'L',
        canceled_by_supervisory_terminal = 'S',
        immediate_order_remaining_quantity_canceled = 'I',
        order_expired_during_matching = 'M',
        invalid_price = 'X',
        invalid_quantity = 'Z',
        invalid_minimum_quantity = 'N',
        invalid_order_type = 'Y',
        invalid_display_type = 'D',
        exceeded_order_value_limit = 'V',
        short_sell_order_restriction = 'i',
        order_not_allowed_at_this_time = 'R',
        flow_control_throttled = 'F',
        margin_order_canceled_due_to_margin_restriction = 'G',
        other = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 16> from_string_map = {{
        {"Canceled By Supervisory Terminal", enum_type::canceled_by_supervisory_terminal},
        {"Exceeded Order Value Limit", enum_type::exceeded_order_value_limit},
        {"Flow Control Throttled", enum_type::flow_control_throttled},
        {"Immediate Order Remaining Quantity Canceled", enum_type::immediate_order_remaining_quantity_canceled},
        {"Invalid Display Type", enum_type::invalid_display_type},
        {"Invalid Minimum Quantity", enum_type::invalid_minimum_quantity},
        {"Invalid Order Type", enum_type::invalid_order_type},
        {"Invalid Price", enum_type::invalid_price},
        {"Invalid Quantity", enum_type::invalid_quantity},
        {"Margin Order Canceled Due To Margin Restriction", enum_type::margin_order_canceled_due_to_margin_restriction},
        {"Order Expired During Matching", enum_type::order_expired_during_matching},
        {"Order Not Allowed At This Time", enum_type::order_not_allowed_at_this_time},
        {"Other", enum_type::other},
        {"Short Sell Order Restriction", enum_type::short_sell_order_restriction},
        {"User Logged Off", enum_type::user_logged_off},
        {"User Requested Cancel", enum_type::user_requested_cancel}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::user_requested_cancel: return "User Requested Cancel";
            case enum_type::user_logged_off: return "User Logged Off";
            case enum_type::canceled_by_supervisory_terminal: return "Canceled By Supervisory Terminal";
            case enum_type::immediate_order_remaining_quantity_canceled: return "Immediate Order Remaining Quantity Canceled";
            case enum_type::order_expired_during_matching: return "Order Expired During Matching";
            case enum_type::invalid_price: return "Invalid Price";
            case enum_type::invalid_quantity: return "Invalid Quantity";
            case enum_type::invalid_minimum_quantity: return "Invalid Minimum Quantity";
            case enum_type::invalid_order_type: return "Invalid Order Type";
            case enum_type::invalid_display_type: return "Invalid Display Type";
            case enum_type::exceeded_order_value_limit: return "Exceeded Order Value Limit";
            case enum_type::short_sell_order_restriction: return "Short Sell Order Restriction";
            case enum_type::order_not_allowed_at_this_time: return "Order Not Allowed At This Time";
            case enum_type::flow_control_throttled: return "Flow Control Throttled";
            case enum_type::margin_order_canceled_due_to_margin_restriction: return "Margin Order Canceled Due To Margin Restriction";
            case enum_type::other: return "Other";
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

    static constexpr const char* name = "order_canceled_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<order_canceled_reason::enum_type>;
    using storage_type = result_type;

    constexpr order_canceled_reason()
     : value{ enum_type{} } {}

    constexpr order_canceled_reason(enum_type v)
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
            set(enum_type::other);
    }

  protected:
    enum_type value;
};
}
