#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Type of Auction:
enum class AuctionType : char {
    Opening = 'O',          // Opening
    Reopening = 'R',        // Reopening
    PriceImprovement = 'P', // Price Improvement
    Exposure = 'I',         // Exposure
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AuctionType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AuctionType value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
