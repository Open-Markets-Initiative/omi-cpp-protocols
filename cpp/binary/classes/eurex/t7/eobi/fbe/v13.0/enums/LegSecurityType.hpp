#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class LegSecurityType : std::uint8_t {
    LegSecurityMultiLeg = 1,      // Leg Security Multi Leg
    LegSecurityUnderlyingLeg = 2, // Leg Security Underlying Leg
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSecurityType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSecurityType value);

} // namespace eurex::t7::eobi::fbe::v13_0
