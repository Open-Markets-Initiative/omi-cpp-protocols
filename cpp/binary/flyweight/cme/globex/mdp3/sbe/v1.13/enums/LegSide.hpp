#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Leg side
enum class LegSide : std::uint8_t {
    BuySide = 1,  // Buy Side
    SellSide = 2, // Sell Side
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSide value);

} // namespace cme::globex::mdp3::sbe::v1_13
