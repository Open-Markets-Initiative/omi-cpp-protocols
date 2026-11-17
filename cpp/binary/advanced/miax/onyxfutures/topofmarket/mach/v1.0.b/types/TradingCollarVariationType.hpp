// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: types/TradingCollarVariationType.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// trading_collar_variation_type
struct trading_collar_variation_type {

    enum class enum_type : char {
        product_dollar_collar_value = 'D',
        product_collar_percentage_value = 'P',
        standard_calendar_spread = 'S',
        equity_calendar_spread = 'E',
        butterfly_spread = 'B'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Butterfly Spread", enum_type::butterfly_spread},
        {"Equity Calendar Spread", enum_type::equity_calendar_spread},
        {"Product Collar Percentage Value", enum_type::product_collar_percentage_value},
        {"Product Dollar Collar Value", enum_type::product_dollar_collar_value},
        {"Standard Calendar Spread", enum_type::standard_calendar_spread}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::product_dollar_collar_value: return "Product Dollar Collar Value";
            case enum_type::product_collar_percentage_value: return "Product Collar Percentage Value";
            case enum_type::standard_calendar_spread: return "Standard Calendar Spread";
            case enum_type::equity_calendar_spread: return "Equity Calendar Spread";
            case enum_type::butterfly_spread: return "Butterfly Spread";
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

    static constexpr const char* name = "trading_collar_variation_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trading_collar_variation_type::enum_type>;
    using storage_type = result_type;

    constexpr trading_collar_variation_type()
     : value{ enum_type{} } {}

    constexpr trading_collar_variation_type(enum_type v)
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
            set(enum_type::butterfly_spread);
    }

  protected:
    enum_type value;
};
}
