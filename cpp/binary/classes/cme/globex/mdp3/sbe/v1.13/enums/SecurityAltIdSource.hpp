#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Identifies class or source of the SecurityAltID (455) value
enum class SecurityAltIdSource : std::uint8_t {
    Cusip = 1, // Cusip
    Isin = 4,  // Isin
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityAltIdSource value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityAltIdSource value);

} // namespace cme::globex::mdp3::sbe::v1_13
