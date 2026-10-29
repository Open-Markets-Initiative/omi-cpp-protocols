#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

// Minimum price increment: 0 - All Penny, 1 - Penny/Nickel, 5 - Nickel/Dime.
enum class PriceResolution : std::uint8_t {
    AllPenny = 0,    // All Penny
    PennyNickel = 1, // Penny Nickel
    NickelDime = 5,  // Nickel Dime
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceResolution value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceResolution value);

} // namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g
