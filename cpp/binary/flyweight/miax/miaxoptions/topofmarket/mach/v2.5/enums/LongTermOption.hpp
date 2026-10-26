#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// "Y" = Far month expiration (as defined by MIAX rules), "N" = Near month expiration (as
// defined by MIAX rules)
enum class LongTermOption : char {
    FarMonthExpiration = 'Y',  // Far Month Expiration
    NearMonthExpiration = 'N', // Near Month Expiration
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LongTermOption value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LongTermOption value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
