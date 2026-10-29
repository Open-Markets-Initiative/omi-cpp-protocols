#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Identifies the trading status applicable to the transaction
enum class SecurityStatus : char {
    NotApplicable = ' ',              // Not Applicable
    TradingHalt = '2',                // Trading Halt
    Resume = '3',                     // Resume
    PriceIndication = '5',            // Price Indication
    TradingRangeIndication = '6',     // Trading Range Indication
    MarketImbalanceBuy = '7',         // Market Imbalance Buy
    MarketImbalanceSell = '8',        // Market Imbalance Sell
    MarketOnCloseImbalanceBuy = '9',  // Market On Close Imbalance Buy
    MarketOnCloseImbalanceSell = 'A', // Market On Close Imbalance Sell
    NoMarketImbalance = 'C',          // No Market Imbalance
    NoMarketOnCloseImbalance = 'D',   // No Market On Close Imbalance
    ShortSaleRestriction = 'E',       // Short Sale Restriction
    LimitUpLimitDown = 'F',           // Limit Up Limit Down
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatus value);

} // namespace siac::cts::output::cta::v2_10
