#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Current state of short sale restriction.
enum class ShortSaleRestriction : char {
    ShortSaleRestrictionIsInEffect = 'Y',    // Short Sale Restriction Is In Effect
    ShortSaleRestrictionIsNotInEffect = 'N', // Short Sale Restriction Is Not In Effect
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ShortSaleRestriction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ShortSaleRestriction value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
