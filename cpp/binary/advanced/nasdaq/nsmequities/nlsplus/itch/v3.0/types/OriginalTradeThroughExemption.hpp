#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// original_trade_through_exemption
struct original_trade_through_exemption {

    enum class enum_type : char {
        intermarket_sweep = 'F',
        opening_print = 'O',
        derivative_priced = '4',
        re_opening_print = '5',
        closing_print = '6',
        qualified_contingent_trade = '7',
        not_applicable = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 7> from_string_map = {{
        {"Closing Print", enum_type::closing_print},
        {"Derivative Priced", enum_type::derivative_priced},
        {"Intermarket Sweep", enum_type::intermarket_sweep},
        {"Not Applicable", enum_type::not_applicable},
        {"Opening Print", enum_type::opening_print},
        {"Qualified Contingent Trade", enum_type::qualified_contingent_trade},
        {"Re Opening Print", enum_type::re_opening_print}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::intermarket_sweep: return "Intermarket Sweep";
            case enum_type::opening_print: return "Opening Print";
            case enum_type::derivative_priced: return "Derivative Priced";
            case enum_type::re_opening_print: return "Re Opening Print";
            case enum_type::closing_print: return "Closing Print";
            case enum_type::qualified_contingent_trade: return "Qualified Contingent Trade";
            case enum_type::not_applicable: return "Not Applicable";
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

    static constexpr const char* name = "original_trade_through_exemption";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<original_trade_through_exemption::enum_type>;
    using storage_type = result_type;

    constexpr original_trade_through_exemption()
     : value{ enum_type{} } {}

    constexpr original_trade_through_exemption(enum_type v)
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
            set(enum_type::not_applicable);
    }

  protected:
    enum_type value;
};
}
