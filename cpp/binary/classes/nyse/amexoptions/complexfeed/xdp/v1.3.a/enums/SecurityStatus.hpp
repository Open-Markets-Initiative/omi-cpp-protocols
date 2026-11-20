// Nyse.AmexOptions.ComplexFeed.Xdp.v1.3.a: enums/SecurityStatus.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// SecurityStatus value
enum class SecurityStatus : char {
    Open = 'O',            // Open
    Close = 'X',           // Close
    Halt = 'S',            // Halt
    EndOfRfqAuction = 'Q', // End Of Rfq Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatus value);

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
