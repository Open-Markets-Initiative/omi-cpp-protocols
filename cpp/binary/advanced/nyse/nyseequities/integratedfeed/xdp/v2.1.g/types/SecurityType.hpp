#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

// security_type
struct security_type {

    enum class enum_type : char {
        common_stock = 'A',
        preferred_stock = 'B',
        warrant = 'C',
        right = 'D',
        corporate_bond = 'E',
        treasury_bond = 'F',
        structured_product = 'G',
        adr_common = 'H',
        adr_preferred = 'I',
        adr_warrants = 'J',
        adr_rights = 'K',
        adr_corporate_bond = 'L',
        ny_registered_share = 'M',
        global_registered_share = 'N',
        index = 'O',
        fund = 'P',
        basket = 'Q',
        unit = 'R',
        liquidating_trust = 'S',
        unknown = 'U'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 20> from_string_map = {{
        {"Adr Common", enum_type::adr_common},
        {"Adr Corporate Bond", enum_type::adr_corporate_bond},
        {"Adr Preferred", enum_type::adr_preferred},
        {"Adr Rights", enum_type::adr_rights},
        {"Adr Warrants", enum_type::adr_warrants},
        {"Basket", enum_type::basket},
        {"Common Stock", enum_type::common_stock},
        {"Corporate Bond", enum_type::corporate_bond},
        {"Fund", enum_type::fund},
        {"Global Registered Share", enum_type::global_registered_share},
        {"Index", enum_type::index},
        {"Liquidating Trust", enum_type::liquidating_trust},
        {"Ny Registered Share", enum_type::ny_registered_share},
        {"Preferred Stock", enum_type::preferred_stock},
        {"Right", enum_type::right},
        {"Structured Product", enum_type::structured_product},
        {"Treasury Bond", enum_type::treasury_bond},
        {"Unit", enum_type::unit},
        {"Unknown", enum_type::unknown},
        {"Warrant", enum_type::warrant}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::common_stock: return "Common Stock";
            case enum_type::preferred_stock: return "Preferred Stock";
            case enum_type::warrant: return "Warrant";
            case enum_type::right: return "Right";
            case enum_type::corporate_bond: return "Corporate Bond";
            case enum_type::treasury_bond: return "Treasury Bond";
            case enum_type::structured_product: return "Structured Product";
            case enum_type::adr_common: return "Adr Common";
            case enum_type::adr_preferred: return "Adr Preferred";
            case enum_type::adr_warrants: return "Adr Warrants";
            case enum_type::adr_rights: return "Adr Rights";
            case enum_type::adr_corporate_bond: return "Adr Corporate Bond";
            case enum_type::ny_registered_share: return "Ny Registered Share";
            case enum_type::global_registered_share: return "Global Registered Share";
            case enum_type::index: return "Index";
            case enum_type::fund: return "Fund";
            case enum_type::basket: return "Basket";
            case enum_type::unit: return "Unit";
            case enum_type::liquidating_trust: return "Liquidating Trust";
            case enum_type::unknown: return "Unknown";
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

    static constexpr const char* name = "security_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_type::enum_type>;
    using storage_type = result_type;

    constexpr security_type()
     : value{ enum_type{} } {}

    constexpr security_type(enum_type v)
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
            set(enum_type::unknown);
    }

  protected:
    enum_type value;
};
}
