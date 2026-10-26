#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// limit_up_limit_down_luld_indicator
struct limit_up_limit_down_luld_indicator {

    enum class enum_type : char {
        limit_up_limit_down_not_applicable = ' ',
        bid_price_above_upper_limit_price_band = 'A',
        offer_price_below_lower_limit_price_band = 'B'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 3> from_string_map = {{
        {"Bid Price Above Upper Limit Price Band", enum_type::bid_price_above_upper_limit_price_band},
        {"Limit Up Limit Down Not Applicable", enum_type::limit_up_limit_down_not_applicable},
        {"Offer Price Below Lower Limit Price Band", enum_type::offer_price_below_lower_limit_price_band}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::limit_up_limit_down_not_applicable: return "Limit Up Limit Down Not Applicable";
            case enum_type::bid_price_above_upper_limit_price_band: return "Bid Price Above Upper Limit Price Band";
            case enum_type::offer_price_below_lower_limit_price_band: return "Offer Price Below Lower Limit Price Band";
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

    static constexpr const char* name = "limit_up_limit_down_luld_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<limit_up_limit_down_luld_indicator::enum_type>;
    using storage_type = result_type;

    constexpr limit_up_limit_down_luld_indicator()
     : value{ enum_type{} } {}

    constexpr limit_up_limit_down_luld_indicator(enum_type v)
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
            set(enum_type::offer_price_below_lower_limit_price_band);
    }

  protected:
    enum_type value;
};
}
