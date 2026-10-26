#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace lseg::millennium::level2::mitch::v11_9 {

// Auction Type
enum class AuctionType : char {
    ClosingAuction = 'C',             // Closing Auction
    OpeningAuction = 'O',             // Opening Auction
    Aesp = 'A',                       // Aesp
    Edsp = 'B',                       // Edsp
    ResumeAuction = 'E',              // Resume Auction
    PeriodicAuction = 'F',            // Periodic Auction
    ScheduledLevel1OnlyAuction = 'G', // Scheduled Level 1 Only Auction
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace lseg::millennium::level2::mitch::v11_9
