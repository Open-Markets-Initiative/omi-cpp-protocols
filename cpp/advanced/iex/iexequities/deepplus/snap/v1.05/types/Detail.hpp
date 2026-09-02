#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

// detail
struct detail {

    enum class enum_type : char {
        no_price_test_in_place = ' ',
        short_sale_price_test_restriction_in_effect_due_to_an_intraday_price_drop_in_the_security = 'A',
        short_sale_price_test_restriction_remains_in_effect_from_prior_day = 'C',
        short_sale_price_test_restriction_deactivated = 'D',
        not_available = 'N'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"No Price Test In Place", enum_type::no_price_test_in_place},
        {"Not Available", enum_type::not_available},
        {"Short Sale Price Test Restriction Deactivated", enum_type::short_sale_price_test_restriction_deactivated},
        {"Short Sale Price Test Restriction In Effect Due To An Intraday Price Drop In The Security", enum_type::short_sale_price_test_restriction_in_effect_due_to_an_intraday_price_drop_in_the_security},
        {"Short Sale Price Test Restriction Remains In Effect From Prior Day", enum_type::short_sale_price_test_restriction_remains_in_effect_from_prior_day}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_price_test_in_place: return "No Price Test In Place";
            case enum_type::short_sale_price_test_restriction_in_effect_due_to_an_intraday_price_drop_in_the_security: return "Short Sale Price Test Restriction In Effect Due To An Intraday Price Drop In The Security";
            case enum_type::short_sale_price_test_restriction_remains_in_effect_from_prior_day: return "Short Sale Price Test Restriction Remains In Effect From Prior Day";
            case enum_type::short_sale_price_test_restriction_deactivated: return "Short Sale Price Test Restriction Deactivated";
            case enum_type::not_available: return "Not Available";
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

    static constexpr const char* name = "detail";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<detail::enum_type>;
    using storage_type = result_type;

    constexpr detail()
     : value{ enum_type::no_price_test_in_place } {}

    constexpr detail(enum_type v)
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
            set(enum_type::not_available);
    }

  protected:
    enum_type value;
};
}
