#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Status field for CUBE/COA
enum class RfqStatus : char {
    StartOfRfqAuction = 'O', // Start Of Rfq Auction
    EndOfRfqAuction = 'Q',   // End Of Rfq Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RfqStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RfqStatus value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
