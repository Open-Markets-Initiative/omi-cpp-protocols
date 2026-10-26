#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Side of order. B - Buy, S - Sell.
enum class OrderSide : char {
    Buy = 'B',  // Buy
    Sell = 'S', // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderSide value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
