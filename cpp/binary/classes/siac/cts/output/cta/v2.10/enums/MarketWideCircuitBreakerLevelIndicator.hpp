#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_10 {

// Identifies the daily established drop level value associated with decline Level 1: 7% of
// Previous Close SP 500 Value
enum class MarketWideCircuitBreakerLevelIndicator : char {
    NotApplicable = ' ',  // Not Applicable
    Level1Breached = '1', // Level 1 Breached
    Level2Breached = '2', // Level 2 Breached
    Level3Breached = '3', // Level 3 Breached
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketWideCircuitBreakerLevelIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketWideCircuitBreakerLevelIndicator value);

} // namespace siac::cts::output::cta::v2_10
