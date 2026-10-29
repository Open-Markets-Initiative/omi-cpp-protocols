#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

// The side of the Unpaired Qty
enum class UnpairedSide : char {
    BuySide = 'B',       // Buy Side
    SellSide = 'S',      // Sell Side
    NotApplicable = ' ', // Not Applicable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UnpairedSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UnpairedSide value);

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
