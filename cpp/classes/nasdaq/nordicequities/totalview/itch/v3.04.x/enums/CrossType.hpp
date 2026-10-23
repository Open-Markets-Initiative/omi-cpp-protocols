#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// The cross session the message is generated for
enum class CrossType : char {
    OpeningCross = 'O',             // Opening Cross
    ScheduledIntradayCross = 'I',   // Scheduled Intraday Cross
    ClosingCross = 'C',             // Closing Cross
    CrossForHaltedSecurities = 'H', // Cross For Halted Securities
    AuctionOnDemand = 'A',          // Auction On Demand
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
