#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// interest_flag
struct interest_flag {

    enum class enum_type : char {
        buy_side = 'B',
        sell_side = 'S',
        both_sides = 'A',
        no_rpi_orders_available = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Both Sides", enum_type::both_sides},
        {"Buy Side", enum_type::buy_side},
        {"No Rpi Orders Available", enum_type::no_rpi_orders_available},
        {"Sell Side", enum_type::sell_side}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::buy_side: return "Buy Side";
            case enum_type::sell_side: return "Sell Side";
            case enum_type::both_sides: return "Both Sides";
            case enum_type::no_rpi_orders_available: return "No Rpi Orders Available";
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

    static constexpr const char* name = "interest_flag";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<interest_flag::enum_type>;
    using storage_type = result_type;

    constexpr interest_flag()
     : value{ enum_type::buy_side } {}

    constexpr interest_flag(enum_type v)
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
            set(enum_type::no_rpi_orders_available);
    }

  protected:
    enum_type value;
};
}
