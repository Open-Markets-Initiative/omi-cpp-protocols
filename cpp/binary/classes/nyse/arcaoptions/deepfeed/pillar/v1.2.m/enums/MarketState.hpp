#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The current Market State.
enum class MarketState : char {
    Preopening = 'P',             // Preopening
    EarlySession = 'E',           // Early Session
    CoreSession = 'O',            // Core Session
    LateSessionNonNyseOnly = 'L', // Late Session Non Nyse Only
    Closed = 'X',                 // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketState value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
