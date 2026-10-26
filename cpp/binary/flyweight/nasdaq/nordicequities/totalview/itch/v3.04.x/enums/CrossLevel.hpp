#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// The level the cross is being generated for
enum class CrossLevel : char {
    Buy = 'B',   // Buy
    Sell = 'S',  // Sell
    Mid = 'M',   // Mid
    Limit = 'L', // Limit
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossLevel value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossLevel value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
