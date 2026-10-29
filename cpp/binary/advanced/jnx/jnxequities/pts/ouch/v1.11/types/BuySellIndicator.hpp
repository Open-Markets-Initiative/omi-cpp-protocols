#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

// buy_sell_indicator
struct buy_sell_indicator {

    enum class enum_type : char {
        buy = 'B',
        sell = 'S',
        short_sell = 'T',
        short_sell_exempt = 'E'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Buy", enum_type::buy},
        {"Sell", enum_type::sell},
        {"Short Sell", enum_type::short_sell},
        {"Short Sell Exempt", enum_type::short_sell_exempt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::buy: return "Buy";
            case enum_type::sell: return "Sell";
            case enum_type::short_sell: return "Short Sell";
            case enum_type::short_sell_exempt: return "Short Sell Exempt";
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

    static constexpr const char* name = "buy_sell_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<buy_sell_indicator::enum_type>;
    using storage_type = result_type;

    constexpr buy_sell_indicator()
     : value{ enum_type{} } {}

    constexpr buy_sell_indicator(enum_type v)
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
            set(enum_type::short_sell_exempt);
    }

  protected:
    enum_type value;
};
}
