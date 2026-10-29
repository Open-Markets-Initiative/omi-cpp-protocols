#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

// B = Buy Order S = Sell Order
enum class SideIndicator : char {
    BuyOrder = 'B',  // Buy Order
    SellOrder = 'S', // Sell Order
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SideIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SideIndicator value);

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
