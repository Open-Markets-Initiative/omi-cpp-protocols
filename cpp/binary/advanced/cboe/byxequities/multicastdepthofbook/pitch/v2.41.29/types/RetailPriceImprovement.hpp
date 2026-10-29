#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

// retail_price_improvement
struct retail_price_improvement {

    enum class enum_type : char {
        buy_side_rpi = 'B',
        sell_side_rpi = 'S',
        buy_and_sell_rpi = 'A',
        no_rpi = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Buy And Sell Rpi", enum_type::buy_and_sell_rpi},
        {"Buy Side Rpi", enum_type::buy_side_rpi},
        {"No Rpi", enum_type::no_rpi},
        {"Sell Side Rpi", enum_type::sell_side_rpi}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::buy_side_rpi: return "Buy Side Rpi";
            case enum_type::sell_side_rpi: return "Sell Side Rpi";
            case enum_type::buy_and_sell_rpi: return "Buy And Sell Rpi";
            case enum_type::no_rpi: return "No Rpi";
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

    static constexpr const char* name = "retail_price_improvement";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<retail_price_improvement::enum_type>;
    using storage_type = result_type;

    constexpr retail_price_improvement()
     : value{ enum_type{} } {}

    constexpr retail_price_improvement(enum_type v)
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
            set(enum_type::no_rpi);
    }

  protected:
    enum_type value;
};
}
