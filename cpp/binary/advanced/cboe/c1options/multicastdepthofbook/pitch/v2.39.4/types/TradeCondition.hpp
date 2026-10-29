#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// trade_condition
struct trade_condition {

    enum class enum_type : char {
        normal_trade = ' ',
        spread_trade = 'S'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Normal Trade", enum_type::normal_trade},
        {"Spread Trade", enum_type::spread_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::normal_trade: return "Normal Trade";
            case enum_type::spread_trade: return "Spread Trade";
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

    static constexpr const char* name = "trade_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_condition::enum_type>;
    using storage_type = result_type;

    constexpr trade_condition()
     : value{ enum_type{} } {}

    constexpr trade_condition(enum_type v)
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
            set(enum_type::spread_trade);
    }

  protected:
    enum_type value;
};
}
