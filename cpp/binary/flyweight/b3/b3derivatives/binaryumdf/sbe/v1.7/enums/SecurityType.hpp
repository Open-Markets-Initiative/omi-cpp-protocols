#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

// securityType
enum class SecurityType : std::uint8_t {
    Cash = 1,      // Cash
    Corp = 2,      // Corp
    Cs = 3,        // Cs
    Dterm = 4,     // Dterm
    Etf = 5,       // Etf
    Fopt = 6,      // Fopt
    Forward = 7,   // Forward
    Fut = 8,       // Fut
    Index = 9,     // Index
    Indexopt = 10, // Indexopt
    Mleg = 11,     // Mleg
    Opt = 12,      // Opt
    Optexer = 13,  // Optexer
    Ps = 14,       // Ps
    Secloan = 15,  // Secloan
    Sopt = 16,     // Sopt
    Spot = 17,     // Spot
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
