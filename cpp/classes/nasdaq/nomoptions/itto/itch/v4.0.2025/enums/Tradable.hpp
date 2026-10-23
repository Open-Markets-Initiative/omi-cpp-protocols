#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Denotes whether or not this option is tradable at the exchange. The allowable values are:
enum class Tradable : char {
    NotTradable = 'N', // Not Tradable
    IsTradable = 'Y',  // Is Tradable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Tradable value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Tradable value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
