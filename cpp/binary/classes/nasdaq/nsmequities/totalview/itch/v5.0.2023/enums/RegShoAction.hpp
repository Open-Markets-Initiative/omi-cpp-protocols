#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Denotes the Reg SHO Short Sale Price Test Restriction status for the issue at the time of
// the message dissemination
enum class RegShoAction : char {
    NoPriceTest = '0',                         // No Price Test
    RegShoShortSalePriceTestRestriction = '1', // Reg Sho Short Sale Price Test Restriction
    TestRestrictionRemains = '2',              // Test Restriction Remains
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RegShoAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RegShoAction value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
