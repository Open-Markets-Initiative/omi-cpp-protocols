#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the type of Market Status message
enum class MarketStatusMessageType : char {
    MarketWideCircuitBreakerDeclineLevelStatus = 'K',      // Market Wide Circuit Breaker Decline Level Status
    MarketWideCircuitBreakerStatus = 'L',                  // Market Wide Circuit Breaker Status
    ApproximateAdjustedVolumeMarketCenter = 'N',           // Approximate Adjusted Volume Market Center
    FractionalApproximateAdjustedVolumeMarketCenter = 'V', // Fractional Approximate Adjusted Volume Market Center
    ApproximateTradesAndTotalDollarValue = 'O',            // Approximate Trades And Total Dollar Value
    CrossingSessionSummary = 'P',                          // Crossing Session Summary
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketStatusMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketStatusMessageType value);

} // namespace siac::cts::output::cta::v2_11_b
