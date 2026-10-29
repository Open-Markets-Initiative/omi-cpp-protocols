#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// unsequenced_message_type
struct unsequenced_message_type {

    enum class enum_type : char {
        enter_order_message = 'O',
        replace_order_message = 'U',
        cancel_order_message = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Cancel Order Message", enum_type::cancel_order_message},
        {"Enter Order Message", enum_type::enter_order_message},
        {"Replace Order Message", enum_type::replace_order_message}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::enter_order_message: return "Enter Order Message";
            case enum_type::replace_order_message: return "Replace Order Message";
            case enum_type::cancel_order_message: return "Cancel Order Message";
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

    static constexpr const char* name = "unsequenced_message_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<unsequenced_message_type::enum_type>;
    using storage_type = result_type;

    constexpr unsequenced_message_type()
     : value{ enum_type{} } {}

    constexpr unsequenced_message_type(enum_type v)
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
            set(enum_type::cancel_order_message);
    }

  protected:
    enum_type value;
};
}
