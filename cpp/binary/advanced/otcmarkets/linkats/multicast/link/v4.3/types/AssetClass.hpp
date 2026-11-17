// OtcMarkets.LinkAts.Multicast.Link.v4.3: types/AssetClass.hpp
#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

// asset_class
struct asset_class {

    enum class enum_type : std::uint8_t {
        equity = 1,
        fixed_income = 2
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Equity", enum_type::equity},
        {"Fixed Income", enum_type::fixed_income}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::equity: return "Equity";
            case enum_type::fixed_income: return "Fixed Income";
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

    static constexpr const char* name = "asset_class";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<asset_class::enum_type>;
    using storage_type = result_type;

    constexpr asset_class()
     : value{ enum_type{} } {}

    constexpr asset_class(enum_type v)
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
            set(enum_type::fixed_income);
    }

  protected:
    enum_type value;
};
}
