#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Identifies class or source of the UnderlyingSecurityAltID (458) value
enum class UnderlyingSecurityAltIdSource : std::uint8_t {
    Cusip = 1, // Cusip
    Isin = 4,  // Isin
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UnderlyingSecurityAltIdSource value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UnderlyingSecurityAltIdSource value);

} // namespace cme::globex::mdp3::sbe::v1_13
