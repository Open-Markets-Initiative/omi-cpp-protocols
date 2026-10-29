#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v1_91 {

// sale_condition
struct sale_condition {

    enum class enum_type : char {
        regular_sale = ' ',
        average_price_trade = 'B',
        cash_trade = 'C',
        automatic_execution = 'E',
        intermarket_sweep_order = 'F',
        price_variation_trade = 'H',
        odd_lot_trade = 'I',
        rule_127_or_155 = 'K',
        sold_last = 'L',
        market_center_official_close = 'M',
        next_day_trade = 'N',
        market_center_opening_trade = 'O',
        prior_reference_price = 'P',
        market_center_official_open = 'Q',
        seller = 'R',
        extended_hours_trade = 'T',
        extended_hours_sold = 'U',
        contingent_trade = 'V',
        cross_trade = 'X',
        sold = 'Z',
        derivatively_priced = '4',
        market_center_reopening_trade = '5',
        market_center_closing_trade = '6',
        qualified_contingent_trade = '7',
        reserved = '8',
        corrected_consolidated_close_price_as_per_listing_market = '9'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 26> from_string_map = {{
        {"Automatic Execution", enum_type::automatic_execution},
        {"Average Price Trade", enum_type::average_price_trade},
        {"Cash Trade", enum_type::cash_trade},
        {"Contingent Trade", enum_type::contingent_trade},
        {"Corrected Consolidated Close Price As Per Listing Market", enum_type::corrected_consolidated_close_price_as_per_listing_market},
        {"Cross Trade", enum_type::cross_trade},
        {"Derivatively Priced", enum_type::derivatively_priced},
        {"Extended Hours Sold", enum_type::extended_hours_sold},
        {"Extended Hours Trade", enum_type::extended_hours_trade},
        {"Intermarket Sweep Order", enum_type::intermarket_sweep_order},
        {"Market Center Closing Trade", enum_type::market_center_closing_trade},
        {"Market Center Official Close", enum_type::market_center_official_close},
        {"Market Center Official Open", enum_type::market_center_official_open},
        {"Market Center Opening Trade", enum_type::market_center_opening_trade},
        {"Market Center Reopening Trade", enum_type::market_center_reopening_trade},
        {"Next Day Trade", enum_type::next_day_trade},
        {"Odd Lot Trade", enum_type::odd_lot_trade},
        {"Price Variation Trade", enum_type::price_variation_trade},
        {"Prior Reference Price", enum_type::prior_reference_price},
        {"Qualified Contingent Trade", enum_type::qualified_contingent_trade},
        {"Regular Sale", enum_type::regular_sale},
        {"Reserved", enum_type::reserved},
        {"Rule 127 Or 155", enum_type::rule_127_or_155},
        {"Seller", enum_type::seller},
        {"Sold", enum_type::sold},
        {"Sold Last", enum_type::sold_last}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::regular_sale: return "Regular Sale";
            case enum_type::average_price_trade: return "Average Price Trade";
            case enum_type::cash_trade: return "Cash Trade";
            case enum_type::automatic_execution: return "Automatic Execution";
            case enum_type::intermarket_sweep_order: return "Intermarket Sweep Order";
            case enum_type::price_variation_trade: return "Price Variation Trade";
            case enum_type::odd_lot_trade: return "Odd Lot Trade";
            case enum_type::rule_127_or_155: return "Rule 127 Or 155";
            case enum_type::sold_last: return "Sold Last";
            case enum_type::market_center_official_close: return "Market Center Official Close";
            case enum_type::next_day_trade: return "Next Day Trade";
            case enum_type::market_center_opening_trade: return "Market Center Opening Trade";
            case enum_type::prior_reference_price: return "Prior Reference Price";
            case enum_type::market_center_official_open: return "Market Center Official Open";
            case enum_type::seller: return "Seller";
            case enum_type::extended_hours_trade: return "Extended Hours Trade";
            case enum_type::extended_hours_sold: return "Extended Hours Sold";
            case enum_type::contingent_trade: return "Contingent Trade";
            case enum_type::cross_trade: return "Cross Trade";
            case enum_type::sold: return "Sold";
            case enum_type::derivatively_priced: return "Derivatively Priced";
            case enum_type::market_center_reopening_trade: return "Market Center Reopening Trade";
            case enum_type::market_center_closing_trade: return "Market Center Closing Trade";
            case enum_type::qualified_contingent_trade: return "Qualified Contingent Trade";
            case enum_type::reserved: return "Reserved";
            case enum_type::corrected_consolidated_close_price_as_per_listing_market: return "Corrected Consolidated Close Price As Per Listing Market";
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

    static constexpr const char* name = "sale_condition";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<sale_condition::enum_type>;
    using storage_type = result_type;

    constexpr sale_condition()
     : value{ enum_type{} } {}

    constexpr sale_condition(enum_type v)
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
            set(enum_type::corrected_consolidated_close_price_as_per_listing_market);
    }

  protected:
    enum_type value;
};
}
