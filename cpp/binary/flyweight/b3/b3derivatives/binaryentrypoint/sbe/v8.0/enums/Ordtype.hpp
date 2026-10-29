#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// ordType
enum class Ordtype : char {
    Market = '1',                    // Market
    Limit = '2',                     // Limit
    StopLoss = '3',                  // Stop Loss
    StopLimit = '4',                 // Stop Limit
    MarketWithLeftoverAsLimit = 'K', // Market With Leftover As Limit
    Rlp = 'W',                       // Rlp
    PeggedMidpoint = 'P',            // Pegged Midpoint
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Ordtype value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Ordtype value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
