#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Identifies originating market
enum class MarketId : std::uint16_t {
    NyseCash = 1,            // Nyse Cash
    EuropeCash = 2,          // Europe Cash
    NyseArcaCash = 3,        // Nyse Arca Cash
    NyseArcaOptions = 4,     // Nyse Arca Options
    NyseArcaBonds = 5,       // Nyse Arca Bonds
    ArcaEdge = 6,            // Arca Edge
    Liffe = 7,               // Liffe
    NyseAmericanOptions = 8, // Nyse American Options
    NyseMktCash = 9,         // Nyse Mkt Cash
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketId value);

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
