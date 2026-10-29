#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::texasequities::integratedfeed::pillar::v2_5_g {

// Round Lots Accepted: Y - Yes, N - No.
enum class RoundLot : char {
    Yes = 'Y', // Yes
    No = 'N',  // No
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RoundLot value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RoundLot value);

} // namespace nyse::texasequities::integratedfeed::pillar::v2_5_g
