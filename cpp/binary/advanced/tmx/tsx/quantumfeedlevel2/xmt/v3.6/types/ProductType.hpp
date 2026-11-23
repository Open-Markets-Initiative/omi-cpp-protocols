// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: types/ProductType.hpp
#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// product_type
struct product_type {

    enum class enum_type : char {
        debenture = 'B',
        equity = 'E',
        mutual_fund = 'M',
        etf = 'F',
        us_equity = 'U',
        bond = 'O'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 6> from_string_map = {{
        {"Bond", enum_type::bond},
        {"Debenture", enum_type::debenture},
        {"Equity", enum_type::equity},
        {"Etf", enum_type::etf},
        {"Mutual Fund", enum_type::mutual_fund},
        {"Us Equity", enum_type::us_equity}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::debenture: return "Debenture";
            case enum_type::equity: return "Equity";
            case enum_type::mutual_fund: return "Mutual Fund";
            case enum_type::etf: return "Etf";
            case enum_type::us_equity: return "Us Equity";
            case enum_type::bond: return "Bond";
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

    static constexpr const char* name = "product_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<product_type::enum_type>;
    using storage_type = result_type;

    constexpr product_type()
     : value{ enum_type{} } {}

    constexpr product_type(enum_type v)
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
            set(enum_type::bond);
    }

  protected:
    enum_type value;
};
}
