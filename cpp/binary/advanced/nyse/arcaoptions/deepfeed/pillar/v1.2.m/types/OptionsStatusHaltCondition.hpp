#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// options_status_halt_condition
struct options_status_halt_condition {

    enum class enum_type : char {
        series_not_delayedhalted = '~',
        option_series_is_halted = 'h'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Option Series Is Halted", enum_type::option_series_is_halted},
        {"Series Not Delayedhalted", enum_type::series_not_delayedhalted}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::series_not_delayedhalted: return "Series Not Delayedhalted";
            case enum_type::option_series_is_halted: return "Option Series Is Halted";
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

    static constexpr const char* name = "options_status_halt_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<options_status_halt_condition::enum_type>;
    using storage_type = result_type;

    constexpr options_status_halt_condition()
     : value{ enum_type{} } {}

    constexpr options_status_halt_condition(enum_type v)
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
            set(enum_type::option_series_is_halted);
    }

  protected:
    enum_type value;
};
}
