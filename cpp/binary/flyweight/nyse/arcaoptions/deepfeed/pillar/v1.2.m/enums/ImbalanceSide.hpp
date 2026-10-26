#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The side of the TotalImbalanceQty.
enum class ImbalanceSide : char {
    BuySide = 'B',                         // Buy Side
    SellSide = 'S',                        // Sell Side
    SpaceOr0X20IndicatesNoImbalance = ' ', // Space Or 0 X 20 Indicates No Imbalance
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ImbalanceSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ImbalanceSide value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
