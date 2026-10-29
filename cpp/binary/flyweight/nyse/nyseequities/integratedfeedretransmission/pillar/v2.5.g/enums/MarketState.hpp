#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// The current Market State, which this msg updates if the Security Status field contains a
// Market State Code.
enum class MarketState : char {
    PreOpening = 'P',             // Pre Opening
    EarlySession = 'E',           // Early Session
    CoreSession = 'O',            // Core Session
    LateSessionNonNyseOnly = 'L', // Late Session Non Nyse Only
    Closed = 'X',                 // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketState value);

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
