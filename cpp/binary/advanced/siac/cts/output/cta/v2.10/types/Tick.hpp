#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_10 {

// tick
struct tick {

    enum class enum_type : char {
        not_applicable = ' ',
        upward = '1',
        downward = '2',
        unchanged_upward = '3',
        unchanged_downward = '4'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Downward", enum_type::downward},
        {"Not Applicable", enum_type::not_applicable},
        {"Unchanged Downward", enum_type::unchanged_downward},
        {"Unchanged Upward", enum_type::unchanged_upward},
        {"Upward", enum_type::upward}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::upward: return "Upward";
            case enum_type::downward: return "Downward";
            case enum_type::unchanged_upward: return "Unchanged Upward";
            case enum_type::unchanged_downward: return "Unchanged Downward";
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

    static constexpr const char* name = "tick";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<tick::enum_type>;
    using storage_type = result_type;

    constexpr tick()
     : value{ enum_type{} } {}

    constexpr tick(enum_type v)
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
            set(enum_type::unchanged_downward);
    }

  protected:
    enum_type value;
};
}
