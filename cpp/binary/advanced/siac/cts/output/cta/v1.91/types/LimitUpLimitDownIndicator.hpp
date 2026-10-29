#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v1_91 {

// limit_up_limit_down_indicator
struct limit_up_limit_down_indicator {

    enum class enum_type : char {
        limit_up_limit_down_not_applicable = ' ',
        limit_up_limit_down_price_band = 'A',
        republished_limit_up_limit_down_price_band = 'B',
        national_best_bid_limit_state_entered = 'C',
        national_best_bid_limit_state_exited = 'D',
        national_best_offer_limit_state_entered = 'E',
        national_best_offer_limit_state_exited = 'F',
        national_best_bid_and_national_best_offer_limit_state_entered = 'G',
        national_best_bid_and_national_best_offer_limit_state_exited = 'H',
        national_best_bid_limit_state_entered_and_national_best_offer_limit_state_exited = 'I',
        national_best_bid_limit_state_exited_and_national_best_offer_limit_state_entered = 'J'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 11> from_string_map = {{
        {"Limit Up Limit Down Not Applicable", enum_type::limit_up_limit_down_not_applicable},
        {"Limit Up Limit Down Price Band", enum_type::limit_up_limit_down_price_band},
        {"National Best Bid And National Best Offer Limit State Entered", enum_type::national_best_bid_and_national_best_offer_limit_state_entered},
        {"National Best Bid And National Best Offer Limit State Exited", enum_type::national_best_bid_and_national_best_offer_limit_state_exited},
        {"National Best Bid Limit State Entered", enum_type::national_best_bid_limit_state_entered},
        {"National Best Bid Limit State Entered And National Best Offer Limit State Exited", enum_type::national_best_bid_limit_state_entered_and_national_best_offer_limit_state_exited},
        {"National Best Bid Limit State Exited", enum_type::national_best_bid_limit_state_exited},
        {"National Best Bid Limit State Exited And National Best Offer Limit State Entered", enum_type::national_best_bid_limit_state_exited_and_national_best_offer_limit_state_entered},
        {"National Best Offer Limit State Entered", enum_type::national_best_offer_limit_state_entered},
        {"National Best Offer Limit State Exited", enum_type::national_best_offer_limit_state_exited},
        {"Republished Limit Up Limit Down Price Band", enum_type::republished_limit_up_limit_down_price_band}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::limit_up_limit_down_not_applicable: return "Limit Up Limit Down Not Applicable";
            case enum_type::limit_up_limit_down_price_band: return "Limit Up Limit Down Price Band";
            case enum_type::republished_limit_up_limit_down_price_band: return "Republished Limit Up Limit Down Price Band";
            case enum_type::national_best_bid_limit_state_entered: return "National Best Bid Limit State Entered";
            case enum_type::national_best_bid_limit_state_exited: return "National Best Bid Limit State Exited";
            case enum_type::national_best_offer_limit_state_entered: return "National Best Offer Limit State Entered";
            case enum_type::national_best_offer_limit_state_exited: return "National Best Offer Limit State Exited";
            case enum_type::national_best_bid_and_national_best_offer_limit_state_entered: return "National Best Bid And National Best Offer Limit State Entered";
            case enum_type::national_best_bid_and_national_best_offer_limit_state_exited: return "National Best Bid And National Best Offer Limit State Exited";
            case enum_type::national_best_bid_limit_state_entered_and_national_best_offer_limit_state_exited: return "National Best Bid Limit State Entered And National Best Offer Limit State Exited";
            case enum_type::national_best_bid_limit_state_exited_and_national_best_offer_limit_state_entered: return "National Best Bid Limit State Exited And National Best Offer Limit State Entered";
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

    static constexpr const char* name = "limit_up_limit_down_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<limit_up_limit_down_indicator::enum_type>;
    using storage_type = result_type;

    constexpr limit_up_limit_down_indicator()
     : value{ enum_type{} } {}

    constexpr limit_up_limit_down_indicator(enum_type v)
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
            set(enum_type::national_best_bid_limit_state_exited_and_national_best_offer_limit_state_entered);
    }

  protected:
    enum_type value;
};
}
