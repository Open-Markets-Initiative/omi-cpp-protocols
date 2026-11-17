// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: types/UnderlyingAssetType.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// underlying_asset_type
struct underlying_asset_type {

    enum class enum_type : char {
        equity_index = 'E',
        commodity_agriculture = 'A'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Commodity Agriculture", enum_type::commodity_agriculture},
        {"Equity Index", enum_type::equity_index}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::equity_index: return "Equity Index";
            case enum_type::commodity_agriculture: return "Commodity Agriculture";
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

    static constexpr const char* name = "underlying_asset_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<underlying_asset_type::enum_type>;
    using storage_type = result_type;

    constexpr underlying_asset_type()
     : value{ enum_type{} } {}

    constexpr underlying_asset_type(enum_type v)
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
            set(enum_type::commodity_agriculture);
    }

  protected:
    enum_type value;
};
}
