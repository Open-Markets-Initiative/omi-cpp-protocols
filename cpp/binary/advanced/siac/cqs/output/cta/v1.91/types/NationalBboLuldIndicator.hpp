#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// national_bbo_luld_indicator
struct national_bbo_luld_indicator {

    enum class enum_type : char {
        not_applicable = ' ',
        national_best_bid_and_or_national_best_offer_are_executable = 'A',
        national_best_bid_below_lower_limit_price_band_and_is_non_executable = 'B',
        national_best_offer_above_upper_limit_price_band_and_is_non_executable = 'C',
        national_best_bid_below_lower_limit_price_band_and_national_best_offer_above_upper_limit_price_band_both_are_non_executable = 'D',
        national_best_bid_equals_upper_limit_price_band_and_is_in_limit_state = 'E',
        national_best_offer_equals_lower_limit_price_band_and_is_in_limit_state = 'F',
        national_best_bid_equals_upper_limit_price_band_and_is_in_limit_state_and_national_best_offer_above_upper_limit_price_band_and_is_non_executable = 'G',
        national_best_bid_below_lower_limit_price_band_and_is_non_executable_and_national_best_offer_equals_lower_limit_price_band_and_is_in_limit_state = 'H',
        national_best_bid_equals_upper_limit_price_band_and_national_best_offer_equals_lower_limit_price_band = 'I'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 10> from_string_map = {{
        {"National Best Bid And Or National Best Offer Are Executable", enum_type::national_best_bid_and_or_national_best_offer_are_executable},
        {"National Best Bid Below Lower Limit Price Band And Is Non Executable", enum_type::national_best_bid_below_lower_limit_price_band_and_is_non_executable},
        {"National Best Bid Below Lower Limit Price Band And Is Non Executable And National Best Offer Equals Lower Limit Price Band And Is In Limit State", enum_type::national_best_bid_below_lower_limit_price_band_and_is_non_executable_and_national_best_offer_equals_lower_limit_price_band_and_is_in_limit_state},
        {"National Best Bid Below Lower Limit Price Band And National Best Offer Above Upper Limit Price Band Both Are Non Executable", enum_type::national_best_bid_below_lower_limit_price_band_and_national_best_offer_above_upper_limit_price_band_both_are_non_executable},
        {"National Best Bid Equals Upper Limit Price Band And Is In Limit State", enum_type::national_best_bid_equals_upper_limit_price_band_and_is_in_limit_state},
        {"National Best Bid Equals Upper Limit Price Band And Is In Limit State And National Best Offer Above Upper Limit Price Band And Is Non Executable", enum_type::national_best_bid_equals_upper_limit_price_band_and_is_in_limit_state_and_national_best_offer_above_upper_limit_price_band_and_is_non_executable},
        {"National Best Bid Equals Upper Limit Price Band And National Best Offer Equals Lower Limit Price Band", enum_type::national_best_bid_equals_upper_limit_price_band_and_national_best_offer_equals_lower_limit_price_band},
        {"National Best Offer Above Upper Limit Price Band And Is Non Executable", enum_type::national_best_offer_above_upper_limit_price_band_and_is_non_executable},
        {"National Best Offer Equals Lower Limit Price Band And Is In Limit State", enum_type::national_best_offer_equals_lower_limit_price_band_and_is_in_limit_state},
        {"Not Applicable", enum_type::not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::national_best_bid_and_or_national_best_offer_are_executable: return "National Best Bid And Or National Best Offer Are Executable";
            case enum_type::national_best_bid_below_lower_limit_price_band_and_is_non_executable: return "National Best Bid Below Lower Limit Price Band And Is Non Executable";
            case enum_type::national_best_offer_above_upper_limit_price_band_and_is_non_executable: return "National Best Offer Above Upper Limit Price Band And Is Non Executable";
            case enum_type::national_best_bid_below_lower_limit_price_band_and_national_best_offer_above_upper_limit_price_band_both_are_non_executable: return "National Best Bid Below Lower Limit Price Band And National Best Offer Above Upper Limit Price Band Both Are Non Executable";
            case enum_type::national_best_bid_equals_upper_limit_price_band_and_is_in_limit_state: return "National Best Bid Equals Upper Limit Price Band And Is In Limit State";
            case enum_type::national_best_offer_equals_lower_limit_price_band_and_is_in_limit_state: return "National Best Offer Equals Lower Limit Price Band And Is In Limit State";
            case enum_type::national_best_bid_equals_upper_limit_price_band_and_is_in_limit_state_and_national_best_offer_above_upper_limit_price_band_and_is_non_executable: return "National Best Bid Equals Upper Limit Price Band And Is In Limit State And National Best Offer Above Upper Limit Price Band And Is Non Executable";
            case enum_type::national_best_bid_below_lower_limit_price_band_and_is_non_executable_and_national_best_offer_equals_lower_limit_price_band_and_is_in_limit_state: return "National Best Bid Below Lower Limit Price Band And Is Non Executable And National Best Offer Equals Lower Limit Price Band And Is In Limit State";
            case enum_type::national_best_bid_equals_upper_limit_price_band_and_national_best_offer_equals_lower_limit_price_band: return "National Best Bid Equals Upper Limit Price Band And National Best Offer Equals Lower Limit Price Band";
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
            set(enum_type::national_best_bid_equals_upper_limit_price_band_and_national_best_offer_equals_lower_limit_price_band);
    }

  protected:
    enum_type value;
};
}
