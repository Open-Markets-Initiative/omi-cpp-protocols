#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// issue_classification
struct issue_classification {

    enum class enum_type : char {
        american_depositary_share = 'A',
        bond = 'B',
        common_stock = 'C',
        depository_receipt = 'F',
        sec_144_a = 'I',
        limited_partnership = 'L',
        notes = 'N',
        ordinary_share = 'O',
        preferred_stock = 'P',
        other_securities = 'Q',
        right = 'R',
        shares_of_beneficial_interest = 'S',
        convertible_debenture = 'T',
        unit = 'U',
        units_of_beneficial_interest = 'V',
        warrant = 'W'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 16> from_string_map = {{
        {"American Depositary Share", enum_type::american_depositary_share},
        {"Bond", enum_type::bond},
        {"Common Stock", enum_type::common_stock},
        {"Convertible Debenture", enum_type::convertible_debenture},
        {"Depository Receipt", enum_type::depository_receipt},
        {"Limited Partnership", enum_type::limited_partnership},
        {"Notes", enum_type::notes},
        {"Ordinary Share", enum_type::ordinary_share},
        {"Other Securities", enum_type::other_securities},
        {"Preferred Stock", enum_type::preferred_stock},
        {"Right", enum_type::right},
        {"Sec 144 A", enum_type::sec_144_a},
        {"Shares Of Beneficial Interest", enum_type::shares_of_beneficial_interest},
        {"Unit", enum_type::unit},
        {"Units Of Beneficial Interest", enum_type::units_of_beneficial_interest},
        {"Warrant", enum_type::warrant}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::american_depositary_share: return "American Depositary Share";
            case enum_type::bond: return "Bond";
            case enum_type::common_stock: return "Common Stock";
            case enum_type::depository_receipt: return "Depository Receipt";
            case enum_type::sec_144_a: return "Sec 144 A";
            case enum_type::limited_partnership: return "Limited Partnership";
            case enum_type::notes: return "Notes";
            case enum_type::ordinary_share: return "Ordinary Share";
            case enum_type::preferred_stock: return "Preferred Stock";
            case enum_type::other_securities: return "Other Securities";
            case enum_type::right: return "Right";
            case enum_type::shares_of_beneficial_interest: return "Shares Of Beneficial Interest";
            case enum_type::convertible_debenture: return "Convertible Debenture";
            case enum_type::unit: return "Unit";
            case enum_type::units_of_beneficial_interest: return "Units Of Beneficial Interest";
            case enum_type::warrant: return "Warrant";
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

    static constexpr const char* name = "issue_classification";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<issue_classification::enum_type>;
    using storage_type = result_type;

    constexpr issue_classification()
     : value{ enum_type::american_depositary_share } {}

    constexpr issue_classification(enum_type v)
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
            set(enum_type::warrant);
    }

  protected:
    enum_type value;
};
}
