#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Round Lots Accepted
enum class RoundLot : char {
    Yes = 'Y', // Yes
    No = 'N',  // No
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RoundLot value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RoundLot value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
