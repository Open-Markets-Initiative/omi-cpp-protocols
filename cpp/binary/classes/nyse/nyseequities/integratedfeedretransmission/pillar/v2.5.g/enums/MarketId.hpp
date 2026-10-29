#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// ID of the Originating Market.
enum class MarketId : std::uint16_t {
    NyseEquities = 1,          // Nyse Equities
    NyseArcaEquities = 3,      // Nyse Arca Equities
    NyseArcaOptions = 4,       // Nyse Arca Options
    NyseBonds = 5,             // Nyse Bonds
    NyseAmericanOptions = 8,   // Nyse American Options
    NyseAmericanEquities = 9,  // Nyse American Equities
    NyseNationalEquities = 10, // Nyse National Equities
    NyseTexasEquities = 11,    // Nyse Texas Equities
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketId value);

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
