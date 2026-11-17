// Databento.MarketData.Normalized.Dbn.v3: enums/Side.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// The side that initiates the event
enum class Side : char {
    Ask = 'A',  // Ask
    Bid = 'B',  // Bid
    None = 'N', // None
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Side value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Side value);

} // namespace databento::marketdata::normalized::dbn::v3
