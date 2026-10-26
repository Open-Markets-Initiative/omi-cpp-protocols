#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// Indicates if NASDAQ system limits order entry for issue
enum class RoundLotsOnly : char {
    RoundLotsOnly = 'Y',  // Round Lots Only
    NoRestrictions = 'N', // No Restrictions
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RoundLotsOnly value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RoundLotsOnly value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
