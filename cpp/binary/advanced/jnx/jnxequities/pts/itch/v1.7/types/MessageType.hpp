#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

// message_type
struct message_type {

    enum class enum_type : char {
        seconds_message = 'T',
        system_event_message = 'S',
        price_tick_size_message = 'L',
        orderbook_directory_message = 'R',
        trading_state_message = 'H',
        short_selling_price_restriction_state_message = 'Y',
        order_added_without_attributes_message = 'A',
        order_added_with_attributes_message = 'F',
        order_executed_message = 'E',
        order_deleted_message = 'D',
        order_replaced_message = 'U'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Order Added With Attributes Message", enum_type::order_added_with_attributes_message},
        {"Order Added Without Attributes Message", enum_type::order_added_without_attributes_message},
        {"Order Deleted Message", enum_type::order_deleted_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Replaced Message", enum_type::order_replaced_message},
        {"Orderbook Directory Message", enum_type::orderbook_directory_message},
        {"Price Tick Size Message", enum_type::price_tick_size_message},
        {"Seconds Message", enum_type::seconds_message},
        {"Short Selling Price Restriction State Message", enum_type::short_selling_price_restriction_state_message},
        {"System Event Message", enum_type::system_event_message},
        {"Trading State Message", enum_type::trading_state_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::seconds_message: return "Seconds Message";
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::price_tick_size_message: return "Price Tick Size Message";
            case enum_type::orderbook_directory_message: return "Orderbook Directory Message";
            case enum_type::trading_state_message: return "Trading State Message";
            case enum_type::short_selling_price_restriction_state_message: return "Short Selling Price Restriction State Message";
            case enum_type::order_added_without_attributes_message: return "Order Added Without Attributes Message";
            case enum_type::order_added_with_attributes_message: return "Order Added With Attributes Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::order_deleted_message: return "Order Deleted Message";
            case enum_type::order_replaced_message: return "Order Replaced Message";
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

    static constexpr const char* name = "message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<message_type::enum_type>;
    using storage_type = result_type;

    constexpr message_type()
     : value{ enum_type{} } {}

    constexpr message_type(enum_type v)
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
            set(enum_type::order_replaced_message);
    }

  protected:
    enum_type value;
};
}
