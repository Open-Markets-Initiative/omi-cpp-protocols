#pragma once

#include <cstddef>
#include <cstdint>
#include <algorithm>
#include <array>
#include <optional>
#include <string_view>
#include "../cache/Required.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

// security_mass_trading_status
struct security_mass_trading_status {

    enum class enum_type : std::uint8_t {
        trading_halt = 2,
        market_imbalance_buy = 7,
        market_imbalance_sell = 8,
        closed = 200,
        restricted = 201,
        book = 202,
        continuous = 203,
        opening_auction = 204,
        opening_auction_freeze = 205,
        intraday_auction = 206,
        intraday_auction_freeze = 207,
        circuit_breaker_auction = 208,
        circuit_breaker_auction_freeze = 209,
        closing_auction = 210,
        closing_auction_freeze = 211,
        ipo_auction = 212,
        ipo_auction_freeze = 213,
        pre_call = 214,
        call = 215,
        freeze = 216,
        trade_at_close = 217,
        retail_pre_call = 218,
        retail_call = 219,
        circuit_breaker_auction_triggered_by_static_limit_breach = 220,
        circuit_breaker_auction_triggered_by_static_limit_breach_freeze = 221,
        no_value = 0xFF
    };

    static constexpr std::array<std::pair<std::string_view, enum_type>, 26> from_string_map = {{
        {"Book", enum_type::book},
        {"Call", enum_type::call},
        {"Circuit Breaker Auction", enum_type::circuit_breaker_auction},
        {"Circuit Breaker Auction Freeze", enum_type::circuit_breaker_auction_freeze},
        {"Circuit Breaker Auction Triggered By Static Limit Breach", enum_type::circuit_breaker_auction_triggered_by_static_limit_breach},
        {"Circuit Breaker Auction Triggered By Static Limit Breach Freeze", enum_type::circuit_breaker_auction_triggered_by_static_limit_breach_freeze},
        {"Closed", enum_type::closed},
        {"Closing Auction", enum_type::closing_auction},
        {"Closing Auction Freeze", enum_type::closing_auction_freeze},
        {"Continuous", enum_type::continuous},
        {"Freeze", enum_type::freeze},
        {"Intraday Auction", enum_type::intraday_auction},
        {"Intraday Auction Freeze", enum_type::intraday_auction_freeze},
        {"Ipo Auction", enum_type::ipo_auction},
        {"Ipo Auction Freeze", enum_type::ipo_auction_freeze},
        {"Market Imbalance Buy", enum_type::market_imbalance_buy},
        {"Market Imbalance Sell", enum_type::market_imbalance_sell},
        {"No Value", enum_type::no_value},
        {"Opening Auction", enum_type::opening_auction},
        {"Opening Auction Freeze", enum_type::opening_auction_freeze},
        {"Pre Call", enum_type::pre_call},
        {"Restricted", enum_type::restricted},
        {"Retail Call", enum_type::retail_call},
        {"Retail Pre Call", enum_type::retail_pre_call},
        {"Trade At Close", enum_type::trade_at_close},
        {"Trading Halt", enum_type::trading_halt}
    }};

    static constexpr std::string_view to_string(enum_type value) {
        switch (value) {
            case enum_type::trading_halt: return "Trading Halt";
            case enum_type::market_imbalance_buy: return "Market Imbalance Buy";
            case enum_type::market_imbalance_sell: return "Market Imbalance Sell";
            case enum_type::closed: return "Closed";
            case enum_type::restricted: return "Restricted";
            case enum_type::book: return "Book";
            case enum_type::continuous: return "Continuous";
            case enum_type::opening_auction: return "Opening Auction";
            case enum_type::opening_auction_freeze: return "Opening Auction Freeze";
            case enum_type::intraday_auction: return "Intraday Auction";
            case enum_type::intraday_auction_freeze: return "Intraday Auction Freeze";
            case enum_type::circuit_breaker_auction: return "Circuit Breaker Auction";
            case enum_type::circuit_breaker_auction_freeze: return "Circuit Breaker Auction Freeze";
            case enum_type::closing_auction: return "Closing Auction";
            case enum_type::closing_auction_freeze: return "Closing Auction Freeze";
            case enum_type::ipo_auction: return "Ipo Auction";
            case enum_type::ipo_auction_freeze: return "Ipo Auction Freeze";
            case enum_type::pre_call: return "Pre Call";
            case enum_type::call: return "Call";
            case enum_type::freeze: return "Freeze";
            case enum_type::trade_at_close: return "Trade At Close";
            case enum_type::retail_pre_call: return "Retail Pre Call";
            case enum_type::retail_call: return "Retail Call";
            case enum_type::circuit_breaker_auction_triggered_by_static_limit_breach: return "Circuit Breaker Auction Triggered By Static Limit Breach";
            case enum_type::circuit_breaker_auction_triggered_by_static_limit_breach_freeze: return "Circuit Breaker Auction Triggered By Static Limit Breach Freeze";
            case enum_type::no_value: return "No Value";
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

    static constexpr const char* name = "security_mass_trading_status";
    static constexpr std::size_t size = 1;
    static constexpr bool is_optional = false;

    using result_type = required<security_mass_trading_status::enum_type>;
    using storage_type = result_type;

    constexpr security_mass_trading_status()
     : value{ enum_type{} } {}

    constexpr security_mass_trading_status(enum_type v)
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
            set(static_cast<enum_type>(0xFF));
    }

  protected:
    enum_type value;
};
}
