#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// "0" = No price test in effect "1" = Reg SHO price test restriction in effect
enum class RegShoAction : char {
    NoPriceTestInEffect = '0',                // No Price Test In Effect
    RegShoPriceTestRestrictionInEffect = '1', // Reg Sho Price Test Restriction In Effect
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RegShoAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RegShoAction value);

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
