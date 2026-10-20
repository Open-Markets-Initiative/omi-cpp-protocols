#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// priceBandType
enum class PriceBandType : std::uint8_t {
    HardLimit = 1,     // Hard Limit
    AuctionLimits = 2, // Auction Limits
    RejectionBand = 3, // Rejection Band
    StaticLimits = 4,  // Static Limits
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceBandType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceBandType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
