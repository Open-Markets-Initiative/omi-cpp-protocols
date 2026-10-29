#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

// The side of the TotalImbalanceQty
enum class ImbalanceSide : char {
    BuySide = 'B',     // Buy Side
    SellSide = 'S',    // Sell Side
    NoImbalance = ' ', // No Imbalance
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ImbalanceSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ImbalanceSide value);

} // namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g
