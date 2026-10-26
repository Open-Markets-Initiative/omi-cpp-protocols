#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// Reason the trading session changed.
enum class SessionChangeReason : std::uint8_t {
    ScheduledTransition = 0,       // Scheduled Transition
    ExtendedByMarketOps = 1,       // Extended By Market Ops
    ShortenedByMarketOps = 2,      // Shortened By Market Ops
    MarketOrderImbalance = 3,      // Market Order Imbalance
    PriceOutsideRange = 4,         // Price Outside Range
    AespCircuitBreakerTripped = 5, // Aesp Circuit Breaker Tripped
    Unavailable = 9,               // Unavailable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SessionChangeReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SessionChangeReason value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
