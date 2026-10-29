#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// sequenced_message_type
struct sequenced_message_type {

    enum class enum_type : char {
        system_event_message = 'S',
        order_accepted_message = 'A',
        order_replaced_message = 'U',
        order_canceled_message = 'C',
        order_aiq_canceled_message = 'D',
        order_executed_message = 'E',
        order_rejected_message = 'J'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Order Accepted Message", enum_type::order_accepted_message},
        {"Order Aiq Canceled Message", enum_type::order_aiq_canceled_message},
        {"Order Canceled Message", enum_type::order_canceled_message},
        {"Order Executed Message", enum_type::order_executed_message},
        {"Order Rejected Message", enum_type::order_rejected_message},
        {"Order Replaced Message", enum_type::order_replaced_message},
        {"System Event Message", enum_type::system_event_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::system_event_message: return "System Event Message";
            case enum_type::order_accepted_message: return "Order Accepted Message";
            case enum_type::order_replaced_message: return "Order Replaced Message";
            case enum_type::order_canceled_message: return "Order Canceled Message";
            case enum_type::order_aiq_canceled_message: return "Order Aiq Canceled Message";
            case enum_type::order_executed_message: return "Order Executed Message";
            case enum_type::order_rejected_message: return "Order Rejected Message";
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

    static constexpr const char* name = "sequenced_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<sequenced_message_type::enum_type>;
    using storage_type = result_type;

    constexpr sequenced_message_type()
     : value{ enum_type{} } {}

    constexpr sequenced_message_type(enum_type v)
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
            set(enum_type::order_rejected_message);
    }

  protected:
    enum_type value;
};
}
