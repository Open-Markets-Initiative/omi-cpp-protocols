#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::complex::pitch::v2_1_18 {

// Auction Opening Type
enum class AuctionOpeningType : char {
    Gth = 'G',           // Gth
    Rth = 'O',           // Rth
    HaltReopening = 'H', // Halt Reopening
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionOpeningType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionOpeningType value);

} // namespace cboe::c1options::complex::pitch::v2_1_18
