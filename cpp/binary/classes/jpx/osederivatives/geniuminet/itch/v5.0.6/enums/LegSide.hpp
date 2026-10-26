#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Leg Side
enum class LegSide : char {
    AsDefined = 'B', // As Defined
    Opposite = 'C',  // Opposite
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSide value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
