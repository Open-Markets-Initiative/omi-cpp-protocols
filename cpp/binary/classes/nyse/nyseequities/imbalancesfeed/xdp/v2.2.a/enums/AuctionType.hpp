#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// Type of auction
enum class AuctionType : char {
    EarlyOpening = 'O',        // Early Opening
    CoreOpening = 'M',         // Core Opening
    Reopening = 'H',           // Reopening
    Closing = 'C',             // Closing
    RegulatoryImbalance = 'R', // Regulatory Imbalance
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
