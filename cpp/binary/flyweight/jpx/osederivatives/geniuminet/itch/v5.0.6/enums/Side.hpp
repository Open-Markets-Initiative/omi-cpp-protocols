#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// B=Buy, S=Sell
enum class Side : char {
    BuyOrder = 'B',  // Buy Order
    SellOrder = 'S', // Sell Order
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Side value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Side value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
