// Databento.MarketData.Normalized.Dbn.v3: enums/SystemCode.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// Type of system message
enum class SystemCode : std::uint8_t {
    Heartbeat = 0,         // Heartbeat
    SubscriptionAck = 1,   // Subscription Ack
    SlowReaderWarning = 2, // Slow Reader Warning
    ReplayCompleted = 3,   // Replay Completed
    EndOfInterval = 4,     // End Of Interval
    UnsubscribeAck = 5,    // Unsubscribe Ack
    Unset = 255,           // Unset
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SystemCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SystemCode value);

} // namespace databento::marketdata::normalized::dbn::v3
