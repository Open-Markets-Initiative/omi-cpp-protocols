#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// Auction type value
enum class AuctionType : char {
    Opening = 'O', // Opening
    Closing = 'C', // Closing
    Halt = 'H',    // Halt
    Ipo = 'I',     // Ipo
    Close = 'M',   // Close
    Sum = 'T',     // Sum
    Bam = 'B',     // Bam
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
