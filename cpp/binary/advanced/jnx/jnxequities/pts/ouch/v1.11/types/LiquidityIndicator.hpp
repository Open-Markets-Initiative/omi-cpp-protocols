#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// liquidity_indicator
struct liquidity_indicator {

    enum class enum_type : char {
        added = 'A',
        removed = 'R'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Added", enum_type::added},
        {"Removed", enum_type::removed}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::added: return "Added";
            case enum_type::removed: return "Removed";
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

    static constexpr const char* name = "liquidity_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<liquidity_indicator::enum_type>;
    using storage_type = result_type;

    constexpr liquidity_indicator()
     : value{ enum_type{} } {}

    constexpr liquidity_indicator(enum_type v)
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
            set(enum_type::removed);
    }

  protected:
    enum_type value;
};
}
