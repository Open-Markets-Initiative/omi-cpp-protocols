#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

// The side of the TotalImbalanceQty
enum class ImbalanceSide : char {
    NoImbalance = ' ', // No Imbalance
    BuySide = 'B',     // Buy Side
    SellSide = 'S',    // Sell Side
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ImbalanceSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ImbalanceSide value);

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f
