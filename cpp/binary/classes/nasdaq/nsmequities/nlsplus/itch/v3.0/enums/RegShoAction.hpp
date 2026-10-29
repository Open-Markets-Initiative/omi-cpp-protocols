#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Denotes the Reg Sho short sale price test restriction status for the issue
enum class RegShoAction : char {
    NoPriceTest = '0',         // No Price Test
    RestrictionInEffect = '1', // Restriction In Effect
    RestrictionRemains = '2',  // Restriction Remains
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RegShoAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RegShoAction value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
