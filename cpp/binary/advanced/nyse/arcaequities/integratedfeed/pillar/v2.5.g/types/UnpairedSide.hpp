#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// unpaired_side
struct unpaired_side {

    enum class enum_type : char {
        buy_side = 'B',
        sell_side = 'S',
        not_applicable = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Buy Side", enum_type::buy_side},
        {"Not Applicable", enum_type::not_applicable},
        {"Sell Side", enum_type::sell_side}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::buy_side: return "Buy Side";
            case enum_type::sell_side: return "Sell Side";
            case enum_type::not_applicable: return "Not Applicable";
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

    static constexpr const char* name = "unpaired_side";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<unpaired_side::enum_type>;
    using storage_type = result_type;

    constexpr unpaired_side()
     : value{ enum_type{} } {}

    constexpr unpaired_side(enum_type v)
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
            set(enum_type::not_applicable);
    }

  protected:
    enum_type value;
};
}
