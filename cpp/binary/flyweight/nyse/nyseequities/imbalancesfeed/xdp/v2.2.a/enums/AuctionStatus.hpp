#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// Indicates whether the auction will run
enum class AuctionStatus : std::uint8_t {
    WillRunOpenClose = 0,              // Will Run Open Close
    WillRunInterest = 1,               // Will Run Interest
    WillNotRunImbalance = 2,           // Will Not Run Imbalance
    WillNotRunTransitionToClosing = 3, // Will Not Run Transition To Closing
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionStatus value);

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
