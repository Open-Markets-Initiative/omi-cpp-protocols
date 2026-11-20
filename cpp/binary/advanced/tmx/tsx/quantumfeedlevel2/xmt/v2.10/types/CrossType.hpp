// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: types/CrossType.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// cross_type
struct cross_type {

    enum class enum_type : char {
        internal = 'I',
        basis = 'B',
        contingent = 'C',
        special_trading_session = 'S',
        volume_weighted_average_price = 'V'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Basis", enum_type::basis},
        {"Contingent", enum_type::contingent},
        {"Internal", enum_type::internal},
        {"Special Trading Session", enum_type::special_trading_session},
        {"Volume Weighted Average Price", enum_type::volume_weighted_average_price}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::internal: return "Internal";
            case enum_type::basis: return "Basis";
            case enum_type::contingent: return "Contingent";
            case enum_type::special_trading_session: return "Special Trading Session";
            case enum_type::volume_weighted_average_price: return "Volume Weighted Average Price";
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

    static constexpr const char* name = "cross_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<cross_type::enum_type>;
    using storage_type = result_type;

    constexpr cross_type()
     : value{ enum_type{} } {}

    constexpr cross_type(enum_type v)
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
            set(enum_type::volume_weighted_average_price);
    }

  protected:
    enum_type value;
};
}
