#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// security_type
struct security_type {

    enum class enum_type : char {
        adr = 'A',
        common_stock = 'C',
        debentures = 'D',
        etf = 'E',
        foreign = 'F',
        american_depository_shares = 'H',
        units_I = 'I',
        miscliquid_trust = 'M',
        ordinary_shares = 'O',
        preferred_stock = 'P',
        rights = 'R',
        shares_of_beneficiary_interest = 'S',
        test = 'T',
        units_U = 'U',
        warrant = 'W',
        index = 'X'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 16> from_string_map = {{
        {"Adr", enum_type::adr},
        {"American Depository Shares", enum_type::american_depository_shares},
        {"Common Stock", enum_type::common_stock},
        {"Debentures", enum_type::debentures},
        {"Etf", enum_type::etf},
        {"Foreign", enum_type::foreign},
        {"Index", enum_type::index},
        {"Miscliquid Trust", enum_type::miscliquid_trust},
        {"Ordinary Shares", enum_type::ordinary_shares},
        {"Preferred Stock", enum_type::preferred_stock},
        {"Rights", enum_type::rights},
        {"Shares Of Beneficiary Interest", enum_type::shares_of_beneficiary_interest},
        {"Test", enum_type::test},
        {"Units", enum_type::units_I},
        {"Units", enum_type::units_U},
        {"Warrant", enum_type::warrant}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::adr: return "Adr";
            case enum_type::common_stock: return "Common Stock";
            case enum_type::debentures: return "Debentures";
            case enum_type::etf: return "Etf";
            case enum_type::foreign: return "Foreign";
            case enum_type::american_depository_shares: return "American Depository Shares";
            case enum_type::units_I: return "Units";
            case enum_type::miscliquid_trust: return "Miscliquid Trust";
            case enum_type::ordinary_shares: return "Ordinary Shares";
            case enum_type::preferred_stock: return "Preferred Stock";
            case enum_type::rights: return "Rights";
            case enum_type::shares_of_beneficiary_interest: return "Shares Of Beneficiary Interest";
            case enum_type::test: return "Test";
            case enum_type::units_U: return "Units";
            case enum_type::warrant: return "Warrant";
            case enum_type::index: return "Index";
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
            set(enum_type::index);
    }

  protected:
    enum_type value;
};
}
