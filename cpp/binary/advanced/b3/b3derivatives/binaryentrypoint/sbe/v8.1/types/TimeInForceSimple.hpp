#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// time_in_force_simple
struct time_in_force_simple {

    enum class enum_type : char {
        day = '0',
        immediate_or_cancel = '3',
        fill_or_kill = '4'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Day", enum_type::day},
        {"Fill Or Kill", enum_type::fill_or_kill},
        {"Immediate Or Cancel", enum_type::immediate_or_cancel}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::day: return "Day";
            case enum_type::immediate_or_cancel: return "Immediate Or Cancel";
            case enum_type::fill_or_kill: return "Fill Or Kill";
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

    static constexpr const char* name = "time_in_force_simple";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<time_in_force_simple::enum_type>;
    using storage_type = result_type;

    constexpr time_in_force_simple()
     : value{ enum_type{} } {}

    constexpr time_in_force_simple(enum_type v)
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
            set(enum_type::fill_or_kill);
    }

  protected:
    enum_type value;
};
}
