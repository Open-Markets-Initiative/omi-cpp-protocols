#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// A, H, Q, S, T
enum class TradingStatus : char {
    AcceptingOrders = 'A',            // Accepting Orders
    Halted = 'H',                     // Halted
    QuoteOnly = 'Q',                  // Quote Only
    ExchangeSpecificSuspension = 'S', // Exchange Specific Suspension
    Trading = 'T',                    // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStatus value);

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
