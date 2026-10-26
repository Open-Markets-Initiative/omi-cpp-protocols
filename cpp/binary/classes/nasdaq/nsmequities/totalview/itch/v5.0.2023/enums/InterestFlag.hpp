#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Interest Flag
enum class InterestFlag : char {
    BuySide = 'B',              // Buy Side
    SellSide = 'S',             // Sell Side
    BothSides = 'A',            // Both Sides
    NoRpiOrdersAvailable = 'N', // No Rpi Orders Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InterestFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InterestFlag value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
