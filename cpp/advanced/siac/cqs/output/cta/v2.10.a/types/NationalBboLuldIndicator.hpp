#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v2_10_a {

// national_bbo_luld_indicator
struct national_bbo_luld_indicator {

    enum class enum_type : char {
        limit_up_limit_down_not_applicable = ' ',
        national_best_bid_andor_national_best_offer_are_executable = 'A',
        national_best_bid_below_lower_limit_price_band = 'B',
        national_best_offer_above_upper_limit_price_band = 'C',
        national_best_bid_below_lower_and_national_best_offer_above_upper_limit_price_band = 'D',
        national_best_bid_equals_upper_limit_price_band = 'E',
        national_best_offer_equals_lower_limit_price_band = 'F',
        national_best_bid_in_limit_state_and_national_best_offer_non_executable = 'G',
        national_best_bid_non_executable_and_national_best_offer_in_limit_state = 'H',
        national_best_bid_equals_upper_and_national_best_offer_equals_lower_limit_price_band = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"Limit Up Limit Down Not Applicable", enum_type::limit_up_limit_down_not_applicable},
        {"National Best Bid Andor National Best Offer Are Executable", enum_type::national_best_bid_andor_national_best_offer_are_executable},
        {"National Best Bid Below Lower And National Best Offer Above Upper Limit Price Band", enum_type::national_best_bid_below_lower_and_national_best_offer_above_upper_limit_price_band},
        {"National Best Bid Below Lower Limit Price Band", enum_type::national_best_bid_below_lower_limit_price_band},
        {"National Best Bid Equals Upper And National Best Offer Equals Lower Limit Price Band", enum_type::national_best_bid_equals_upper_and_national_best_offer_equals_lower_limit_price_band},
        {"National Best Bid Equals Upper Limit Price Band", enum_type::national_best_bid_equals_upper_limit_price_band},
        {"National Best Bid In Limit State And National Best Offer Non Executable", enum_type::national_best_bid_in_limit_state_and_national_best_offer_non_executable},
        {"National Best Bid Non Executable And National Best Offer In Limit State", enum_type::national_best_bid_non_executable_and_national_best_offer_in_limit_state},
        {"National Best Offer Above Upper Limit Price Band", enum_type::national_best_offer_above_upper_limit_price_band},
        {"National Best Offer Equals Lower Limit Price Band", enum_type::national_best_offer_equals_lower_limit_price_band}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::limit_up_limit_down_not_applicable: return "Limit Up Limit Down Not Applicable";
            case enum_type::national_best_bid_andor_national_best_offer_are_executable: return "National Best Bid Andor National Best Offer Are Executable";
            case enum_type::national_best_bid_below_lower_limit_price_band: return "National Best Bid Below Lower Limit Price Band";
            case enum_type::national_best_offer_above_upper_limit_price_band: return "National Best Offer Above Upper Limit Price Band";
            case enum_type::national_best_bid_below_lower_and_national_best_offer_above_upper_limit_price_band: return "National Best Bid Below Lower And National Best Offer Above Upper Limit Price Band";
            case enum_type::national_best_bid_equals_upper_limit_price_band: return "National Best Bid Equals Upper Limit Price Band";
            case enum_type::national_best_offer_equals_lower_limit_price_band: return "National Best Offer Equals Lower Limit Price Band";
            case enum_type::national_best_bid_in_limit_state_and_national_best_offer_non_executable: return "National Best Bid In Limit State And National Best Offer Non Executable";
            case enum_type::national_best_bid_non_executable_and_national_best_offer_in_limit_state: return "National Best Bid Non Executable And National Best Offer In Limit State";
            case enum_type::national_best_bid_equals_upper_and_national_best_offer_equals_lower_limit_price_band: return "National Best Bid Equals Upper And National Best Offer Equals Lower Limit Price Band";
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

    static constexpr const char* name = "national_bbo_luld_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<national_bbo_luld_indicator::enum_type>;
    using storage_type = result_type;

    constexpr national_bbo_luld_indicator()
     : value{ enum_type{} } {}

    constexpr national_bbo_luld_indicator(enum_type v)
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
            set(enum_type::national_best_bid_equals_upper_and_national_best_offer_equals_lower_limit_price_band);
    }

  protected:
    enum_type value;
};
}
