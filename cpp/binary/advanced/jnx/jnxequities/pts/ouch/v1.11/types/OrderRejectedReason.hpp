#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// order_rejected_reason
struct order_rejected_reason {

    enum class enum_type : char {
        trading_halt = 'H',
        invalid_order_book_identifier = 'S',
        invalid_price = 'X',
        invalid_quantity = 'Z',
        invalid_minimum_quantity = 'N',
        invalid_order_type = 'Y',
        invalid_display_type = 'D',
        exceeded_order_value_limit = 'V',
        short_sell_order_restriction = 'i',
        order_not_allowed_at_this_time = 'R',
        flow_control_throttled = 'F',
        invalid_margin_specification = 'G',
        mpid_not_allowed_for_this_port = 'L',
        no_permission_to_enter_order_on_given_board = 'c',
        other = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 15> from_string_map = {{
        {"Exceeded Order Value Limit", enum_type::exceeded_order_value_limit},
        {"Flow Control Throttled", enum_type::flow_control_throttled},
        {"Invalid Display Type", enum_type::invalid_display_type},
        {"Invalid Margin Specification", enum_type::invalid_margin_specification},
        {"Invalid Minimum Quantity", enum_type::invalid_minimum_quantity},
        {"Invalid Order Book Identifier", enum_type::invalid_order_book_identifier},
        {"Invalid Order Type", enum_type::invalid_order_type},
        {"Invalid Price", enum_type::invalid_price},
        {"Invalid Quantity", enum_type::invalid_quantity},
        {"Mpid Not Allowed For This Port", enum_type::mpid_not_allowed_for_this_port},
        {"No Permission To Enter Order On Given Board", enum_type::no_permission_to_enter_order_on_given_board},
        {"Order Not Allowed At This Time", enum_type::order_not_allowed_at_this_time},
        {"Other", enum_type::other},
        {"Short Sell Order Restriction", enum_type::short_sell_order_restriction},
        {"Trading Halt", enum_type::trading_halt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trading_halt: return "Trading Halt";
            case enum_type::invalid_order_book_identifier: return "Invalid Order Book Identifier";
            case enum_type::invalid_price: return "Invalid Price";
            case enum_type::invalid_quantity: return "Invalid Quantity";
            case enum_type::invalid_minimum_quantity: return "Invalid Minimum Quantity";
            case enum_type::invalid_order_type: return "Invalid Order Type";
            case enum_type::invalid_display_type: return "Invalid Display Type";
            case enum_type::exceeded_order_value_limit: return "Exceeded Order Value Limit";
            case enum_type::short_sell_order_restriction: return "Short Sell Order Restriction";
            case enum_type::order_not_allowed_at_this_time: return "Order Not Allowed At This Time";
            case enum_type::flow_control_throttled: return "Flow Control Throttled";
            case enum_type::invalid_margin_specification: return "Invalid Margin Specification";
            case enum_type::mpid_not_allowed_for_this_port: return "Mpid Not Allowed For This Port";
            case enum_type::no_permission_to_enter_order_on_given_board: return "No Permission To Enter Order On Given Board";
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

    static constexpr const char* name = "order_rejected_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<order_rejected_reason::enum_type>;
    using storage_type = result_type;

    constexpr order_rejected_reason()
     : value{ enum_type{} } {}

    constexpr order_rejected_reason(enum_type v)
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
