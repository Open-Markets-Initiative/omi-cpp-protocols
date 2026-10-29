#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

// Indicates the side of the leg
enum class Side : char {
    Buy = 'B',    // Buy
    Sell = 'S',   // Sell
    Hidden = ' ', // Hidden
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Side value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Side value);

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
