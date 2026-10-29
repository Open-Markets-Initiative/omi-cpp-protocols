#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// This status field is used for CUBE/COA (Type = C).
enum class RfqStatus : char {
    Start = 'O', // Start
    End = 'Q',   // End
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RfqStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RfqStatus value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
