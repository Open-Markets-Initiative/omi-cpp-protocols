#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

// The side of the Unpaired Qty
enum class UnpairedSide : char {
    NotApplicable = ' ', // Not Applicable
    BuySide = 'B',       // Buy Side
    SellSide = 'S',      // Sell Side
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UnpairedSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UnpairedSide value);

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
