// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/IsDark.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Indicates The Passive Side Of The Trade Is Dark
enum class IsDark : char {
    Yes = 'Y', // Yes
    No = 'N',  // No
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IsDark value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IsDark value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
