#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Reserved for future use
enum class Opening : char {
    None = ' ',                     // None
    MarketCenterOpeningTrade = 'O', // Market Center Opening Trade
    ReopeningTrade = '5',           // Reopening Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Opening value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Opening value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
