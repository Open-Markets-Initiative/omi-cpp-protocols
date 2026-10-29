#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// display
struct display {

    enum class enum_type : char {
        unused = ' ',
        post_only = 'P'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Post Only", enum_type::post_only},
        {"Unused", enum_type::unused}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::unused: return "Unused";
            case enum_type::post_only: return "Post Only";
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

    static constexpr const char* name = "display";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<display::enum_type>;
    using storage_type = result_type;

    constexpr display()
     : value{ enum_type{} } {}

    constexpr display(enum_type v)
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
            set(enum_type::post_only);
    }

  protected:
    enum_type value;
};
}
