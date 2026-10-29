#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cqs::output::cta::v1_91 {

// national_bbo_indicator
struct national_bbo_indicator {

    enum class enum_type : char {
        not_included = ' ',
        no_best_bid_change_or_best_offer_change = 'A',
        no_best_bid_change_quote_contains_best_offer = 'B',
        no_best_bid_change_best_offer_short_appendage = 'C',
        no_best_bid_change_best_offer_long_appendage = 'D',
        no_best_bid_change_no_best_offer = 'E',
        quote_contains_best_bid_no_best_offer_change = 'F',
        quote_contains_best_bid_quote_contains_best_offer = 'G',
        quote_contains_best_bid_best_offer_short_appendage = 'H',
        quote_contains_best_bid_best_offer_long_appendage = 'I',
        quote_contains_best_bid_no_best_offer = 'J',
        no_best_bid_no_best_offer_change = 'K',
        no_best_bid_quote_contains_best_offer = 'L',
        no_best_bid_best_offer_short_appendage = 'M',
        no_best_bid_best_offer_long_appendage = 'N',
        no_best_bid_no_best_offer = 'O',
        best_bid_short_appendage_no_best_offer_change = 'P',
        best_bid_long_appendage_no_best_offer_change = 'Q',
        best_bid_short_appendage_quote_contains_best_offer = 'R',
        best_bid_long_appendage_quote_contains_best_offer = 'S',
        best_bid_short_appendage_best_offer_short_appendage = 'T',
        best_bid_long_appendage_best_offer_long_appendage = 'U',
        best_bid_short_appendage_no_best_offer = 'V',
        best_bid_long_appendage_no_best_offer = 'W'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 24> from_string_map = {{
        {"Best Bid Long Appendage Best Offer Long Appendage", enum_type::best_bid_long_appendage_best_offer_long_appendage},
        {"Best Bid Long Appendage No Best Offer", enum_type::best_bid_long_appendage_no_best_offer},
        {"Best Bid Long Appendage No Best Offer Change", enum_type::best_bid_long_appendage_no_best_offer_change},
        {"Best Bid Long Appendage Quote Contains Best Offer", enum_type::best_bid_long_appendage_quote_contains_best_offer},
        {"Best Bid Short Appendage Best Offer Short Appendage", enum_type::best_bid_short_appendage_best_offer_short_appendage},
        {"Best Bid Short Appendage No Best Offer", enum_type::best_bid_short_appendage_no_best_offer},
        {"Best Bid Short Appendage No Best Offer Change", enum_type::best_bid_short_appendage_no_best_offer_change},
        {"Best Bid Short Appendage Quote Contains Best Offer", enum_type::best_bid_short_appendage_quote_contains_best_offer},
        {"No Best Bid Best Offer Long Appendage", enum_type::no_best_bid_best_offer_long_appendage},
        {"No Best Bid Best Offer Short Appendage", enum_type::no_best_bid_best_offer_short_appendage},
        {"No Best Bid Change Best Offer Long Appendage", enum_type::no_best_bid_change_best_offer_long_appendage},
        {"No Best Bid Change Best Offer Short Appendage", enum_type::no_best_bid_change_best_offer_short_appendage},
        {"No Best Bid Change No Best Offer", enum_type::no_best_bid_change_no_best_offer},
        {"No Best Bid Change Or Best Offer Change", enum_type::no_best_bid_change_or_best_offer_change},
        {"No Best Bid Change Quote Contains Best Offer", enum_type::no_best_bid_change_quote_contains_best_offer},
        {"No Best Bid No Best Offer", enum_type::no_best_bid_no_best_offer},
        {"No Best Bid No Best Offer Change", enum_type::no_best_bid_no_best_offer_change},
        {"No Best Bid Quote Contains Best Offer", enum_type::no_best_bid_quote_contains_best_offer},
        {"Not Included", enum_type::not_included},
        {"Quote Contains Best Bid Best Offer Long Appendage", enum_type::quote_contains_best_bid_best_offer_long_appendage},
        {"Quote Contains Best Bid Best Offer Short Appendage", enum_type::quote_contains_best_bid_best_offer_short_appendage},
        {"Quote Contains Best Bid No Best Offer", enum_type::quote_contains_best_bid_no_best_offer},
        {"Quote Contains Best Bid No Best Offer Change", enum_type::quote_contains_best_bid_no_best_offer_change},
        {"Quote Contains Best Bid Quote Contains Best Offer", enum_type::quote_contains_best_bid_quote_contains_best_offer}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::not_included: return "Not Included";
            case enum_type::no_best_bid_change_or_best_offer_change: return "No Best Bid Change Or Best Offer Change";
            case enum_type::no_best_bid_change_quote_contains_best_offer: return "No Best Bid Change Quote Contains Best Offer";
            case enum_type::no_best_bid_change_best_offer_short_appendage: return "No Best Bid Change Best Offer Short Appendage";
            case enum_type::no_best_bid_change_best_offer_long_appendage: return "No Best Bid Change Best Offer Long Appendage";
            case enum_type::no_best_bid_change_no_best_offer: return "No Best Bid Change No Best Offer";
            case enum_type::quote_contains_best_bid_no_best_offer_change: return "Quote Contains Best Bid No Best Offer Change";
            case enum_type::quote_contains_best_bid_quote_contains_best_offer: return "Quote Contains Best Bid Quote Contains Best Offer";
            case enum_type::quote_contains_best_bid_best_offer_short_appendage: return "Quote Contains Best Bid Best Offer Short Appendage";
            case enum_type::quote_contains_best_bid_best_offer_long_appendage: return "Quote Contains Best Bid Best Offer Long Appendage";
            case enum_type::quote_contains_best_bid_no_best_offer: return "Quote Contains Best Bid No Best Offer";
            case enum_type::no_best_bid_no_best_offer_change: return "No Best Bid No Best Offer Change";
            case enum_type::no_best_bid_quote_contains_best_offer: return "No Best Bid Quote Contains Best Offer";
            case enum_type::no_best_bid_best_offer_short_appendage: return "No Best Bid Best Offer Short Appendage";
            case enum_type::no_best_bid_best_offer_long_appendage: return "No Best Bid Best Offer Long Appendage";
            case enum_type::no_best_bid_no_best_offer: return "No Best Bid No Best Offer";
            case enum_type::best_bid_short_appendage_no_best_offer_change: return "Best Bid Short Appendage No Best Offer Change";
            case enum_type::best_bid_long_appendage_no_best_offer_change: return "Best Bid Long Appendage No Best Offer Change";
            case enum_type::best_bid_short_appendage_quote_contains_best_offer: return "Best Bid Short Appendage Quote Contains Best Offer";
            case enum_type::best_bid_long_appendage_quote_contains_best_offer: return "Best Bid Long Appendage Quote Contains Best Offer";
            case enum_type::best_bid_short_appendage_best_offer_short_appendage: return "Best Bid Short Appendage Best Offer Short Appendage";
            case enum_type::best_bid_long_appendage_best_offer_long_appendage: return "Best Bid Long Appendage Best Offer Long Appendage";
            case enum_type::best_bid_short_appendage_no_best_offer: return "Best Bid Short Appendage No Best Offer";
            case enum_type::best_bid_long_appendage_no_best_offer: return "Best Bid Long Appendage No Best Offer";
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

    static constexpr const char* name = "national_bbo_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<national_bbo_indicator::enum_type>;
    using storage_type = result_type;

    constexpr national_bbo_indicator()
     : value{ enum_type{} } {}

    constexpr national_bbo_indicator(enum_type v)
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
            set(enum_type::best_bid_long_appendage_no_best_offer);
    }

  protected:
    enum_type value;
};
}
