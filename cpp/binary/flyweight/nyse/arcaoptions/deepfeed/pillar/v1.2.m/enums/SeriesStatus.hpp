#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The new status that this series is transitioning to.
enum class SeriesStatus : char {
    TradingHalt = '4',          // Trading Halt
    Resume = '5',               // Resume
    Suspend = '6',              // Suspend
    Preopening = 'P',           // Preopening
    BeginAcceptingOrders = 'B', // Begin Accepting Orders
    CoreSession = 'O',          // Core Session
    Closed = 'X',               // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SeriesStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SeriesStatus value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
