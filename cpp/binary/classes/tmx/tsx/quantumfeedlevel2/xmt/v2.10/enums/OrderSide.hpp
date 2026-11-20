// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/OrderSide.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Market Side Of An Order
enum class OrderSide : char {
    Buy = 'B',  // Buy
    Sell = 'S', // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderSide value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
