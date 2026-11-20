// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/NonResident.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// A Terms Marker Indicating That Trade Participant Is Not A Canadian Resident
enum class NonResident : char {
    Yes = 'Y', // Yes
    No = 'N',  // No
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(NonResident value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, NonResident value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
