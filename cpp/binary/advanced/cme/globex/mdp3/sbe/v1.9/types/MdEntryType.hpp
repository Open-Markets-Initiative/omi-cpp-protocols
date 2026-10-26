#pragma once

#include <cstddef>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace cme::mdp3::v9 {

// md_entry_type
struct md_entry_type {

    enum class enum_type : char {
        bid = '0',
        offer = '1',
        trade = '2',
        open_price = '4',
        settlement_price = '6',
        trading_session_high_price = '7',
        trading_session_low_price = '8',
        cleared_volume = 'B',
        open_interest = 'C',
        implied_bid = 'E',
        implied_offer = 'F',
        book_reset = 'J',
        session_high_bid = 'N',
        session_low_offer = 'O',
        fixing_price = 'W',
        electronic_volume = 'e',
        threshold_limits_and_price_band_variation = 'g'
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 17> from_string_map = {{
        {"Bid", enum_type::bid},
        {"Book Reset", enum_type::book_reset},
        {"Cleared Volume", enum_type::cleared_volume},
        {"Electronic Volume", enum_type::electronic_volume},
        {"Fixing Price", enum_type::fixing_price},
        {"Implied Bid", enum_type::implied_bid},
        {"Implied Offer", enum_type::implied_offer},
        {"Offer", enum_type::offer},
        {"Open Interest", enum_type::open_interest},
        {"Open Price", enum_type::open_price},
        {"Session High Bid", enum_type::session_high_bid},
        {"Session Low Offer", enum_type::session_low_offer},
        {"Settlement Price", enum_type::settlement_price},
        {"Threshold Limits And Price Band Variation", enum_type::threshold_limits_and_price_band_variation},
        {"Trade", enum_type::trade},
        {"Trading Session High Price", enum_type::trading_session_high_price},
        {"Trading Session Low Price", enum_type::trading_session_low_price}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::bid: return "Bid";
            case enum_type::offer: return "Offer";
            case enum_type::trade: return "Trade";
            case enum_type::open_price: return "Open Price";
            case enum_type::settlement_price: return "Settlement Price";
            case enum_type::trading_session_high_price: return "Trading Session High Price";
            case enum_type::trading_session_low_price: return "Trading Session Low Price";
            case enum_type::cleared_volume: return "Cleared Volume";
            case enum_type::open_interest: return "Open Interest";
            case enum_type::implied_bid: return "Implied Bid";
            case enum_type::implied_offer: return "Implied Offer";
            case enum_type::book_reset: return "Book Reset";
            case enum_type::session_high_bid: return "Session High Bid";
            case enum_type::session_low_offer: return "Session Low Offer";
            case enum_type::fixing_price: return "Fixing Price";
            case enum_type::electronic_volume: return "Electronic Volume";
            case enum_type::threshold_limits_and_price_band_variation: return "Threshold Limits And Price Band Variation";
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

    static constexpr const char* name = "md_entry_type";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<md_entry_type::enum_type>;
    using storage_type = result_type;

    constexpr md_entry_type()
     : value{ enum_type{} } {}

    constexpr md_entry_type(enum_type v)
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
            set(enum_type::threshold_limits_and_price_band_variation);
    }

  protected:
    enum_type value;
};
}
