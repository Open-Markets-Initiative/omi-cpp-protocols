#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Minimum Price Variation for this option
enum class Mpv : char {
    PennyEverywhere = 'E', // Penny Everywhere
    Scaled = 'S',          // Scaled
    PennyPilot = 'P',      // Penny Pilot
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Mpv value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Mpv value);

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
