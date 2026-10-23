#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Side of the RFQ.
enum class RfqSide : char {
    Buy = 'B',  // Buy
    Sell = 'S', // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RfqSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RfqSide value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
