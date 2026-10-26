#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Denotes the Reg SHO Short Sale Price Test Restriction status for the issue at the time of
// the message dissemination.
enum class RegShoAction : char {
    NoPriceTest = '0',         // No Price Test
    RestrictionInEffect = '1', // Restriction In Effect
    RestrictionRemains = '2',  // Restriction Remains
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RegShoAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RegShoAction value);

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
