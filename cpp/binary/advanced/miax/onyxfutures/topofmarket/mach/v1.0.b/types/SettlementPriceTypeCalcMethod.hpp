// Miax.OnyxFutures.TopOfMarket.Mach.v1.0.b: types/SettlementPriceTypeCalcMethod.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// settlement_price_type_calc_method
struct settlement_price_type_calc_method {

    enum class enum_type : char {
        actual = 'A',
        theoretical = 'T'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 2> from_string_map = {{
        {"Actual", enum_type::actual},
        {"Theoretical", enum_type::theoretical}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::actual: return "Actual";
            case enum_type::theoretical: return "Theoretical";
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

    static constexpr const char* name = "settlement_price_type_calc_method";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<settlement_price_type_calc_method::enum_type>;
    using storage_type = result_type;

    constexpr settlement_price_type_calc_method()
     : value{ enum_type{} } {}

    constexpr settlement_price_type_calc_method(enum_type v)
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
            set(enum_type::theoretical);
    }

  protected:
    enum_type value;
};
}
