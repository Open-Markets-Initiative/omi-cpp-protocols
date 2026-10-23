#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

// Session Change Reason
enum class SessionChangeReason : std::uint8_t {
    ScheduledTransition = 0,            // Scheduled Transition
    ExtendedByMarketOps = 1,            // Extended By Market Ops
    ShortenedByMarketOps = 2,           // Shortened By Market Ops
    MarketOrderImbalance = 3,           // Market Order Imbalance
    PriceOutsideRange = 4,              // Price Outside Range
    UnavailableRecoveryServiceOnly = 9, // Unavailable Recovery Service Only
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SessionChangeReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SessionChangeReason value);

} // namespace lseg::millennium::level2::mitch::v11_9
