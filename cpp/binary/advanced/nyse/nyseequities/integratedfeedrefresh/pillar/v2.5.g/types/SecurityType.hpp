#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::nyseequities::integratedfeedrefresh::pillar::v2_5_g {

// security_type
struct security_type {

    enum class enum_type : char {
        adr = 'A',
        common_stock = 'C',
        debentures = 'D',
        etf = 'E',
        foreign = 'F',
        us_depositary_shares = 'H',
        units = 'I',
        index_linked_notes = 'L',
        miscliquid_trust = 'M',
        ordinary_shares = 'O',
        preferred_stock = 'P',
        rights = 'R',
        shares_of_beneficiary_interest = 'S',
        test = 'T',
        closed_end_fund = 'U',
        warrant = 'W'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 16> from_string_map = {{
        {"Adr", enum_type::adr},
        {"Closed End Fund", enum_type::closed_end_fund},
        {"Common Stock", enum_type::common_stock},
        {"Debentures", enum_type::debentures},
        {"Etf", enum_type::etf},
        {"Foreign", enum_type::foreign},
        {"Index Linked Notes", enum_type::index_linked_notes},
        {"Miscliquid Trust", enum_type::miscliquid_trust},
        {"Ordinary Shares", enum_type::ordinary_shares},
        {"Preferred Stock", enum_type::preferred_stock},
        {"Rights", enum_type::rights},
        {"Shares Of Beneficiary Interest", enum_type::shares_of_beneficiary_interest},
        {"Test", enum_type::test},
        {"Units", enum_type::units},
        {"Us Depositary Shares", enum_type::us_depositary_shares},
        {"Warrant", enum_type::warrant}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::adr: return "Adr";
            case enum_type::common_stock: return "Common Stock";
            case enum_type::debentures: return "Debentures";
            case enum_type::etf: return "Etf";
            case enum_type::foreign: return "Foreign";
            case enum_type::us_depositary_shares: return "Us Depositary Shares";
            case enum_type::units: return "Units";
            case enum_type::index_linked_notes: return "Index Linked Notes";
            case enum_type::miscliquid_trust: return "Miscliquid Trust";
            case enum_type::ordinary_shares: return "Ordinary Shares";
            case enum_type::preferred_stock: return "Preferred Stock";
            case enum_type::rights: return "Rights";
            case enum_type::shares_of_beneficiary_interest: return "Shares Of Beneficiary Interest";
            case enum_type::test: return "Test";
            case enum_type::closed_end_fund: return "Closed End Fund";
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
            set(enum_type::warrant);
    }

  protected:
    enum_type value;
};
}
