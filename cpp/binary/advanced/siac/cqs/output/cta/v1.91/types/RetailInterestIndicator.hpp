#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// retail_interest_indicator
struct retail_interest_indicator {

    enum class enum_type : char {
        not_applicable = ' ',
        retail_interest_on_bid_quote = 'A',
        retail_interest_on_offer_quote = 'B',
        retail_interest_on_both_the_bid_and_offer_quotes = 'C'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 4> from_string_map = {{
        {"Not Applicable", enum_type::not_applicable},
        {"Retail Interest On Bid Quote", enum_type::retail_interest_on_bid_quote},
        {"Retail Interest On Both The Bid And Offer Quotes", enum_type::retail_interest_on_both_the_bid_and_offer_quotes},
        {"Retail Interest On Offer Quote", enum_type::retail_interest_on_offer_quote}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_applicable: return "Not Applicable";
            case enum_type::retail_interest_on_bid_quote: return "Retail Interest On Bid Quote";
            case enum_type::retail_interest_on_offer_quote: return "Retail Interest On Offer Quote";
            case enum_type::retail_interest_on_both_the_bid_and_offer_quotes: return "Retail Interest On Both The Bid And Offer Quotes";
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

    static constexpr const char* name = "retail_interest_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<retail_interest_indicator::enum_type>;
    using storage_type = result_type;

    constexpr retail_interest_indicator()
     : value{ enum_type{} } {}

    constexpr retail_interest_indicator(enum_type v)
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
            set(enum_type::retail_interest_on_both_the_bid_and_offer_quotes);
    }

  protected:
    enum_type value;
};
}
