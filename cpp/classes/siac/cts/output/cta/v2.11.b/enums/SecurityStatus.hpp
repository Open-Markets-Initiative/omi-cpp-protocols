#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the trading status applicable to the transaction
enum class SecurityStatus : char {
    SecurityStatusNotApplicable = ' ', // Security Status Not Applicable
    Reserved1 = '1',                   // Reserved 1
    TradingHalt = '2',                 // Trading Halt
    Resume = '3',                      // Resume
    Reserved4 = '4',                   // Reserved 4
    PriceIndication = '5',             // Price Indication
    TradingRangeIndication = '6',      // Trading Range Indication
    MarketImbalanceBuy = '7',          // Market Imbalance Buy
    MarketImbalanceSell = '8',         // Market Imbalance Sell
    ClosingImbalanceBuy = '9',         // Closing Imbalance Buy
    ClosingImbalanceSell = 'A',        // Closing Imbalance Sell
    ReservedB = 'B',                   // Reserved B
    NoMarketImbalance = 'C',           // No Market Imbalance
    NoClosingImbalance = 'D',          // No Closing Imbalance
    ShortSaleRestriction = 'E',        // Short Sale Restriction
    LimitUpLimitDown = 'F',            // Limit Up Limit Down
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatus value);

} // namespace siac::cts::output::cta::v2_11_b
