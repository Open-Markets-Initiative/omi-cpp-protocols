#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Minimum Price Variation for this option. See Notes below for further explanation:
enum class Mpv : char {
    Everywhere = 'E', // Everywhere
    Scaled = 'S',     // Scaled
    Pilot = 'P',      // Pilot
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Mpv value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Mpv value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
