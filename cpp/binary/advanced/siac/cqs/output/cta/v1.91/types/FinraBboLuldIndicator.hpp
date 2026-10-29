#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// finra_bbo_luld_indicator
struct finra_bbo_luld_indicator {

    enum class enum_type : char {
        limit_up_limit_down_not_applicable = ' ',
        finra_best_bid_and_or_finra_best_offer_are_executable = 'A',
        finra_best_bid_below_lower_limit_price_band_and_finra_best_bid_is_non_executable = 'B',
        finra_best_offer_above_upper_limit_price_band_and_finra_best_offer_is_non_executable = 'C',
        best_bid_below_lower_limit_price_band_and_best_offer_above_upper_limit_price_band_best_bid_and_best_offer_are_non_executable_for_finra = 'D'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 5> from_string_map = {{
        {"Best Bid Below Lower Limit Price Band And Best Offer Above Upper Limit Price Band Best Bid And Best Offer Are Non Executable For Finra", enum_type::best_bid_below_lower_limit_price_band_and_best_offer_above_upper_limit_price_band_best_bid_and_best_offer_are_non_executable_for_finra},
        {"Finra Best Bid And Or Finra Best Offer Are Executable", enum_type::finra_best_bid_and_or_finra_best_offer_are_executable},
        {"Finra Best Bid Below Lower Limit Price Band And Finra Best Bid Is Non Executable", enum_type::finra_best_bid_below_lower_limit_price_band_and_finra_best_bid_is_non_executable},
        {"Finra Best Offer Above Upper Limit Price Band And Finra Best Offer Is Non Executable", enum_type::finra_best_offer_above_upper_limit_price_band_and_finra_best_offer_is_non_executable},
        {"Limit Up Limit Down Not Applicable", enum_type::limit_up_limit_down_not_applicable}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::limit_up_limit_down_not_applicable: return "Limit Up Limit Down Not Applicable";
            case enum_type::finra_best_bid_and_or_finra_best_offer_are_executable: return "Finra Best Bid And Or Finra Best Offer Are Executable";
            case enum_type::finra_best_bid_below_lower_limit_price_band_and_finra_best_bid_is_non_executable: return "Finra Best Bid Below Lower Limit Price Band And Finra Best Bid Is Non Executable";
            case enum_type::finra_best_offer_above_upper_limit_price_band_and_finra_best_offer_is_non_executable: return "Finra Best Offer Above Upper Limit Price Band And Finra Best Offer Is Non Executable";
            case enum_type::best_bid_below_lower_limit_price_band_and_best_offer_above_upper_limit_price_band_best_bid_and_best_offer_are_non_executable_for_finra: return "Best Bid Below Lower Limit Price Band And Best Offer Above Upper Limit Price Band Best Bid And Best Offer Are Non Executable For Finra";
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

    static constexpr const char* name = "finra_bbo_luld_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<finra_bbo_luld_indicator::enum_type>;
    using storage_type = result_type;

    constexpr finra_bbo_luld_indicator()
     : value{ enum_type{} } {}

    constexpr finra_bbo_luld_indicator(enum_type v)
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
            set(enum_type::best_bid_below_lower_limit_price_band_and_best_offer_above_upper_limit_price_band_best_bid_and_best_offer_are_non_executable_for_finra);
    }

  protected:
    enum_type value;
};
}
