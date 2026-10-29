#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace siac::cts::output::cta::v2_9 {

// trade_through_exempt_reason
struct trade_through_exempt_reason {

    enum class enum_type : char {
        no_reason = ' ',
        intermarket_sweep_order = 'F',
        market_center_opening_trade = 'O',
        derivatively_priced = '4',
        market_center_reopening_trade = '5',
        market_center_closing_trade = '6',
        qualified_contingent_trade = '7',
        reserved = '8',
        corrected_consolidated_close_price_as_per_listing_market = '9'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 9> from_string_map = {{
        {"Corrected Consolidated Close Price As Per Listing Market", enum_type::corrected_consolidated_close_price_as_per_listing_market},
        {"Derivatively Priced", enum_type::derivatively_priced},
        {"Intermarket Sweep Order", enum_type::intermarket_sweep_order},
        {"Market Center Closing Trade", enum_type::market_center_closing_trade},
        {"Market Center Opening Trade", enum_type::market_center_opening_trade},
        {"Market Center Reopening Trade", enum_type::market_center_reopening_trade},
        {"No Reason", enum_type::no_reason},
        {"Qualified Contingent Trade", enum_type::qualified_contingent_trade},
        {"Reserved", enum_type::reserved}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::no_reason: return "No Reason";
            case enum_type::intermarket_sweep_order: return "Intermarket Sweep Order";
            case enum_type::market_center_opening_trade: return "Market Center Opening Trade";
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

    static constexpr const char* name = "trade_through_exempt_reason";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<trade_through_exempt_reason::enum_type>;
    using storage_type = result_type;

    constexpr trade_through_exempt_reason()
     : value{ enum_type{} } {}

    constexpr trade_through_exempt_reason(enum_type v)
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
