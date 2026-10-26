#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// financial_product
struct financial_product {

    enum class enum_type : std::uint8_t {
        stock = 1,
        equity_warrant = 2,
        equity_right = 3,
        bond = 4,
        lottery_bond_series = 6,
        convertible = 7,
        warrant = 8,
        unit_trust_certificate = 11,
        index_fund_unit = 12
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Bond", enum_type::bond},
        {"Convertible", enum_type::convertible},
        {"Equity Right", enum_type::equity_right},
        {"Equity Warrant", enum_type::equity_warrant},
        {"Index Fund Unit", enum_type::index_fund_unit},
        {"Lottery Bond Series", enum_type::lottery_bond_series},
        {"Stock", enum_type::stock},
        {"Unit Trust Certificate", enum_type::unit_trust_certificate},
        {"Warrant", enum_type::warrant}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::stock: return "Stock";
            case enum_type::equity_warrant: return "Equity Warrant";
            case enum_type::equity_right: return "Equity Right";
            case enum_type::bond: return "Bond";
            case enum_type::lottery_bond_series: return "Lottery Bond Series";
            case enum_type::convertible: return "Convertible";
            case enum_type::warrant: return "Warrant";
            case enum_type::unit_trust_certificate: return "Unit Trust Certificate";
            case enum_type::index_fund_unit: return "Index Fund Unit";
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

    static constexpr const char* name = "financial_product";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<financial_product::enum_type>;
    using storage_type = result_type;

    constexpr financial_product()
     : value{ enum_type{} } {}

    constexpr financial_product(enum_type v)
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
            set(enum_type::index_fund_unit);
    }

  protected:
    enum_type value;
};
}
