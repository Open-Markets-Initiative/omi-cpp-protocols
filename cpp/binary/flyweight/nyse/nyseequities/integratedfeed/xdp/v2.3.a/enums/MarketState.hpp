#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// The current Market State, which this msg updates if the Security Status field contains a
// Market State Code.
enum class MarketState : char {
    Preopening = 'P',   // Preopening
    EarlySession = 'E', // Early Session
    CoreSession = 'O',  // Core Session
    LateSession = 'L',  // Late Session
    Closed = 'X',       // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketState value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
