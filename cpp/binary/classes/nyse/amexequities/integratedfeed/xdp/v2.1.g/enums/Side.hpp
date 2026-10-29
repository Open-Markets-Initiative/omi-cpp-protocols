#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// The side of the order. Valid values: ‘B’ – Buy ‘S’ – Sell
enum class Side : char {
    Buy = 'B',  // Buy
    Sell = 'S', // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Side value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Side value);

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
