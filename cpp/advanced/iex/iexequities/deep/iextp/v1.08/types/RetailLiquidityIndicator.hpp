#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deep::iextp::v1_08 {

// retail_liquidity_indicator
struct retail_liquidity_indicator {

    enum class enum_type : char {
        not_applicable = ' ',
        buy_interest = 'A',
        sell_interest = 'B',
        buy_and_sell_interest = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Buy And Sell Interest", enum_type::buy_and_sell_interest},
        {"Buy Interest", enum_type::buy_interest},
        {"Not Applicable", enum_type::not_applicable},
        {"Sell Interest", enum_type::sell_interest}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::buy_interest: return "Buy Interest";
            case enum_type::sell_interest: return "Sell Interest";
            case enum_type::buy_and_sell_interest: return "Buy And Sell Interest";
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

    static constexpr const char* name = "retail_liquidity_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<retail_liquidity_indicator::enum_type>;
    using storage_type = result_type;

    constexpr retail_liquidity_indicator()
     : value{ enum_type::not_applicable } {}

    constexpr retail_liquidity_indicator(enum_type v)
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
            set(enum_type::buy_and_sell_interest);
    }

  protected:
    enum_type value;
};
}
