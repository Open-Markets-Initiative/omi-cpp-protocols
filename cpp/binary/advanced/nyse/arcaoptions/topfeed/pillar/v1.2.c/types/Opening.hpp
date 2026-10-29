#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// opening
struct opening {

    enum class enum_type : char {
        none = ' ',
        market_center_opening_trade = 'O',
        reopening_trade = '5'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Market Center Opening Trade", enum_type::market_center_opening_trade},
        {"None", enum_type::none},
        {"Reopening Trade", enum_type::reopening_trade}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::none: return "None";
            case enum_type::market_center_opening_trade: return "Market Center Opening Trade";
            case enum_type::reopening_trade: return "Reopening Trade";
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

    static constexpr const char* name = "opening";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<opening::enum_type>;
    using storage_type = result_type;

    constexpr opening()
     : value{ enum_type{} } {}

    constexpr opening(enum_type v)
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
            set(enum_type::reopening_trade);
    }

  protected:
    enum_type value;
};
}
