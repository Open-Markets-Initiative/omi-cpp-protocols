#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// SecurityStatus value
enum class SecurityStatus : char {
    LightUpADarkSeries = 'L', // Light Up A Dark Series
    OpenADarkSeries = 'N',    // Open A Dark Series
    Open = 'O',               // Open
    Close = 'X',              // Close
    Halt = 'S',               // Halt
    Unhalt = 'U',             // Unhalt
    UnhaltADarkSeries = 'T',  // Unhalt A Dark Series
    EndOfRfqAuction = 'Q',    // End Of Rfq Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatus value);

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
