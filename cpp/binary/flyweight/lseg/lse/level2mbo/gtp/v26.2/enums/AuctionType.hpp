#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::lse::level2mbo::gtp::v26_2 {

// The value in this field is only relevant when Trade Type is 1.
enum class AuctionType : char {
    ClosingAuction = 'C',  // Closing Auction
    OpeningAuction = 'O',  // Opening Auction
    Aesp = 'A',            // Aesp
    Edsp = 'B',            // Edsp
    ResumeAuction = 'E',   // Resume Auction
    PeriodicAuction = 'F', // Periodic Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace lseg::lse::level2mbo::gtp::v26_2
