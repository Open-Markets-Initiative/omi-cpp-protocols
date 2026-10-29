#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Settlement related conditions. Valid values:
enum class Transaction : char {
    OpeningTradeInSequence = 'H',    // Opening Trade In Sequence
    OpeningTradeOutOfSequence = 'F', // Opening Trade Out Of Sequence
    InSequence = 'D',                // In Sequence
    OutOfSequence = 'B',             // Out Of Sequence
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Transaction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Transaction value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
