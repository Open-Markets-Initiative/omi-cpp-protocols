#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_9 {

// Market Status message type
enum class MarketStatusMessageType : char {
    MarketWideCircuitBreakerDeclineLevelStatusMessage = 'K', // Market Wide Circuit Breaker Decline Level Status Message
    MarketWideCircuitBreakerStatusMessage = 'L',             // Market Wide Circuit Breaker Status Message
    ApproximateAdjustedVolumeMarketCenterMessage = 'N',      // Approximate Adjusted Volume Market Center Message
    ApproximateTradesAndTotalDollarValueMessage = 'O',       // Approximate Trades And Total Dollar Value Message
    CrossingSessionSummaryMessage = 'P',                     // Crossing Session Summary Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketStatusMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketStatusMessageType value);

} // namespace siac::cts::output::cta::v2_9
