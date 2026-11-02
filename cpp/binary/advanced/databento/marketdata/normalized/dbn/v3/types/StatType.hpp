#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace databento::marketdata::normalized::dbn::v3 {

// stat_type
struct stat_type {

    enum class enum_type : std::uint16_t {
        opening_price = 1,
        indicative_opening_price = 2,
        settlement_price = 3,
        trading_session_low_price = 4,
        trading_session_high_price = 5,
        cleared_volume = 6,
        lowest_offer = 7,
        highest_bid = 8,
        open_interest = 9,
        fixing_price = 10,
        close_price = 11,
        net_change = 12,
        vwap = 13,
        volatility = 14,
        delta = 15,
        uncrossing_price = 16,
        upper_price_limit = 17,
        lower_price_limit = 18,
        block_volume = 19,
        indicative_close_price = 20,
        mwcb_level1 = 21,
        mwcb_level2 = 22,
        mwcb_level3 = 23,
        auction_collar_reference_price = 24,
        auction_collar_upper_price = 25,
        auction_collar_lower_price = 26,
        venue_specific_volume1 = 10001,
        venue_specific_price1 = 10002
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 28> from_string_map = {{
        {"Auction Collar Lower Price", enum_type::auction_collar_lower_price},
        {"Auction Collar Reference Price", enum_type::auction_collar_reference_price},
        {"Auction Collar Upper Price", enum_type::auction_collar_upper_price},
        {"Block Volume", enum_type::block_volume},
        {"Cleared Volume", enum_type::cleared_volume},
        {"Close Price", enum_type::close_price},
        {"Delta", enum_type::delta},
        {"Fixing Price", enum_type::fixing_price},
        {"Highest Bid", enum_type::highest_bid},
        {"Indicative Close Price", enum_type::indicative_close_price},
        {"Indicative Opening Price", enum_type::indicative_opening_price},
        {"Lower Price Limit", enum_type::lower_price_limit},
        {"Lowest Offer", enum_type::lowest_offer},
        {"Mwcb Level1", enum_type::mwcb_level1},
        {"Mwcb Level2", enum_type::mwcb_level2},
        {"Mwcb Level3", enum_type::mwcb_level3},
        {"Net Change", enum_type::net_change},
        {"Open Interest", enum_type::open_interest},
        {"Opening Price", enum_type::opening_price},
        {"Settlement Price", enum_type::settlement_price},
        {"Trading Session High Price", enum_type::trading_session_high_price},
        {"Trading Session Low Price", enum_type::trading_session_low_price},
        {"Uncrossing Price", enum_type::uncrossing_price},
        {"Upper Price Limit", enum_type::upper_price_limit},
        {"Venue Specific Price1", enum_type::venue_specific_price1},
        {"Venue Specific Volume1", enum_type::venue_specific_volume1},
        {"Volatility", enum_type::volatility},
        {"Vwap", enum_type::vwap}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::opening_price: return "Opening Price";
            case enum_type::indicative_opening_price: return "Indicative Opening Price";
            case enum_type::settlement_price: return "Settlement Price";
            case enum_type::trading_session_low_price: return "Trading Session Low Price";
            case enum_type::trading_session_high_price: return "Trading Session High Price";
            case enum_type::cleared_volume: return "Cleared Volume";
            case enum_type::lowest_offer: return "Lowest Offer";
            case enum_type::highest_bid: return "Highest Bid";
            case enum_type::open_interest: return "Open Interest";
            case enum_type::fixing_price: return "Fixing Price";
            case enum_type::close_price: return "Close Price";
            case enum_type::net_change: return "Net Change";
            case enum_type::vwap: return "Vwap";
            case enum_type::volatility: return "Volatility";
            case enum_type::delta: return "Delta";
            case enum_type::uncrossing_price: return "Uncrossing Price";
            case enum_type::upper_price_limit: return "Upper Price Limit";
            case enum_type::lower_price_limit: return "Lower Price Limit";
            case enum_type::block_volume: return "Block Volume";
            case enum_type::indicative_close_price: return "Indicative Close Price";
            case enum_type::mwcb_level1: return "Mwcb Level1";
            case enum_type::mwcb_level2: return "Mwcb Level2";
            case enum_type::mwcb_level3: return "Mwcb Level3";
            case enum_type::auction_collar_reference_price: return "Auction Collar Reference Price";
            case enum_type::auction_collar_upper_price: return "Auction Collar Upper Price";
            case enum_type::auction_collar_lower_price: return "Auction Collar Lower Price";
            case enum_type::venue_specific_volume1: return "Venue Specific Volume1";
            case enum_type::venue_specific_price1: return "Venue Specific Price1";
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

    static constexpr const char* name = "stat_type";
    static constexpr std::size_t size = 2;
    static constexpr bool is_optional = false;

    using result_type = required<stat_type::enum_type>;
    using storage_type = result_type;

    constexpr stat_type()
     : value{ enum_type{} } {}

    constexpr stat_type(enum_type v)
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
            set(enum_type::venue_specific_price1);
    }

  protected:
    enum_type value;
};
}
