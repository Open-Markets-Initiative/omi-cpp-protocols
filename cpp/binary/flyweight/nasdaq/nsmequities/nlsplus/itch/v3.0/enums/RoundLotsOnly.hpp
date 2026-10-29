#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Indicates if Nasdaq system limits order entry for the issue
enum class RoundLotsOnly : char {
    RoundLotsOnly = 'Y', // Round Lots Only
    NoRestriction = 'N', // No Restriction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RoundLotsOnly value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RoundLotsOnly value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
