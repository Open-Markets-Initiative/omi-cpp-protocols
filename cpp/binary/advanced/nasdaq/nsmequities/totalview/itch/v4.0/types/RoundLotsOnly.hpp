#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// round_lots_only
struct round_lots_only {

    enum class enum_type : char {
        round_lots_only = 'Y',
        odd_mixed_lots_allowed = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Odd Mixed Lots Allowed", enum_type::odd_mixed_lots_allowed},
        {"Round Lots Only", enum_type::round_lots_only}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::round_lots_only: return "Round Lots Only";
            case enum_type::odd_mixed_lots_allowed: return "Odd Mixed Lots Allowed";
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

    static constexpr const char* name = "round_lots_only";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<round_lots_only::enum_type>;
    using storage_type = result_type;

    constexpr round_lots_only()
     : value{ enum_type{} } {}

    constexpr round_lots_only(enum_type v)
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
            set(enum_type::odd_mixed_lots_allowed);
    }

  protected:
    enum_type value;
};
}
