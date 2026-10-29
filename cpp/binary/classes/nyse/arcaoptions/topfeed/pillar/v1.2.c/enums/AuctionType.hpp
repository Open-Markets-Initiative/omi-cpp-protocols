#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// AuctionType
enum class AuctionType : char {
    Opening = 'O',   // Opening
    Reopening = 'H', // Reopening
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
