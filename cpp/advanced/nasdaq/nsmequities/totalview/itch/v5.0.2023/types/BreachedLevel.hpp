#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// breached_level
struct breached_level {

    enum class enum_type : char {
        level_1 = '1',
        level_2 = '2',
        level_3 = '3'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Level 1", enum_type::level_1},
        {"Level 2", enum_type::level_2},
        {"Level 3", enum_type::level_3}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::level_1: return "Level 1";
            case enum_type::level_2: return "Level 2";
            case enum_type::level_3: return "Level 3";
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

    static constexpr const char* name = "breached_level";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<breached_level::enum_type>;
    using storage_type = result_type;

    constexpr breached_level()
     : value{ enum_type::level_1 } {}

    constexpr breached_level(enum_type v)
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
            set(enum_type::level_3);
    }

  protected:
    enum_type value;
};
}
