#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::opra::output::obi::v6_2 {

// bbo_indicator
struct bbo_indicator {

    enum class enum_type : char {
        no_best_bid_change_or_best_offer_change = 'A',
        no_best_bid_change_quote_contains_best_offer = 'B',
        no_best_bid_change_best_offer_appendage = 'C',
        no_best_bid_change_no_best_offer = 'D',
        quote_contains_best_bid_no_best_offer_change = 'E',
        quote_contains_best_bid_quote_contains_best_offer = 'F',
        quote_contains_best_bid_best_offer_appendage = 'G',
        quote_contains_best_bid_no_best_offer = 'H',
        no_best_bid_no_best_offer_change = 'I',
        no_best_bid_quote_contains_best_offer = 'J',
        no_best_bid_best_offer_appendage = 'K',
        no_best_bid_no_best_offer = 'L',
        best_bid_appendage_no_best_offer_change = 'M',
        best_bid_appendage_quote_contains_best_offer = 'N',
        best_bid_appendage_best_offer_appendage = 'O',
        best_bid_appendage_no_best_offer = 'P',
        not_included_in_the_bbo = ' '
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Best Bid Appendage Best Offer Appendage", enum_type::best_bid_appendage_best_offer_appendage},
        {"Best Bid Appendage No Best Offer", enum_type::best_bid_appendage_no_best_offer},
        {"Best Bid Appendage No Best Offer Change", enum_type::best_bid_appendage_no_best_offer_change},
        {"Best Bid Appendage Quote Contains Best Offer", enum_type::best_bid_appendage_quote_contains_best_offer},
        {"No Best Bid Best Offer Appendage", enum_type::no_best_bid_best_offer_appendage},
        {"No Best Bid Change Best Offer Appendage", enum_type::no_best_bid_change_best_offer_appendage},
        {"No Best Bid Change No Best Offer", enum_type::no_best_bid_change_no_best_offer},
        {"No Best Bid Change Or Best Offer Change", enum_type::no_best_bid_change_or_best_offer_change},
        {"No Best Bid Change Quote Contains Best Offer", enum_type::no_best_bid_change_quote_contains_best_offer},
        {"No Best Bid No Best Offer", enum_type::no_best_bid_no_best_offer},
        {"No Best Bid No Best Offer Change", enum_type::no_best_bid_no_best_offer_change},
        {"No Best Bid Quote Contains Best Offer", enum_type::no_best_bid_quote_contains_best_offer},
        {"Not Included In The Bbo", enum_type::not_included_in_the_bbo},
        {"Quote Contains Best Bid Best Offer Appendage", enum_type::quote_contains_best_bid_best_offer_appendage},
        {"Quote Contains Best Bid No Best Offer", enum_type::quote_contains_best_bid_no_best_offer},
        {"Quote Contains Best Bid No Best Offer Change", enum_type::quote_contains_best_bid_no_best_offer_change},
        {"Quote Contains Best Bid Quote Contains Best Offer", enum_type::quote_contains_best_bid_quote_contains_best_offer}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_best_bid_change_or_best_offer_change: return "No Best Bid Change Or Best Offer Change";
            case enum_type::no_best_bid_change_quote_contains_best_offer: return "No Best Bid Change Quote Contains Best Offer";
            case enum_type::no_best_bid_change_best_offer_appendage: return "No Best Bid Change Best Offer Appendage";
            case enum_type::no_best_bid_change_no_best_offer: return "No Best Bid Change No Best Offer";
            case enum_type::quote_contains_best_bid_no_best_offer_change: return "Quote Contains Best Bid No Best Offer Change";
            case enum_type::quote_contains_best_bid_quote_contains_best_offer: return "Quote Contains Best Bid Quote Contains Best Offer";
            case enum_type::quote_contains_best_bid_best_offer_appendage: return "Quote Contains Best Bid Best Offer Appendage";
            case enum_type::quote_contains_best_bid_no_best_offer: return "Quote Contains Best Bid No Best Offer";
            case enum_type::no_best_bid_no_best_offer_change: return "No Best Bid No Best Offer Change";
            case enum_type::no_best_bid_quote_contains_best_offer: return "No Best Bid Quote Contains Best Offer";
            case enum_type::no_best_bid_best_offer_appendage: return "No Best Bid Best Offer Appendage";
            case enum_type::no_best_bid_no_best_offer: return "No Best Bid No Best Offer";
            case enum_type::best_bid_appendage_no_best_offer_change: return "Best Bid Appendage No Best Offer Change";
            case enum_type::best_bid_appendage_quote_contains_best_offer: return "Best Bid Appendage Quote Contains Best Offer";
            case enum_type::best_bid_appendage_best_offer_appendage: return "Best Bid Appendage Best Offer Appendage";
            case enum_type::best_bid_appendage_no_best_offer: return "Best Bid Appendage No Best Offer";
            case enum_type::not_included_in_the_bbo: return "Not Included In The Bbo";
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

    static constexpr const char* name = "bbo_indicator";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<bbo_indicator::enum_type>;
    using storage_type = result_type;

    constexpr bbo_indicator()
     : value{ enum_type{} } {}

    constexpr bbo_indicator(enum_type v)
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
            set(enum_type::not_included_in_the_bbo);
    }

  protected:
    enum_type value;
};
}
