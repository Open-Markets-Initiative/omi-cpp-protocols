#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Denotes whether or not this option is tradable at the exchange:
enum class Tradable : char {
    Tradable = 'Y',    // Tradable
    NotTradable = 'N', // Not Tradable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Tradable value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Tradable value);

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
