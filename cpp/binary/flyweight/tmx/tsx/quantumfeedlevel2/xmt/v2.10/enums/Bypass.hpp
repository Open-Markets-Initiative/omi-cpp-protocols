// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/Bypass.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// An Indicator For Bypass Crosses Which Can Be Printed Outside Of The Protected Nbbo And Are
// Not Subject To Cross Interference
enum class Bypass : char {
    TheOrderIsABypass = 'Y',    // The Order Is A Bypass
    TheOrderIsNotABypass = 'N', // The Order Is Not A Bypass
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Bypass value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Bypass value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
