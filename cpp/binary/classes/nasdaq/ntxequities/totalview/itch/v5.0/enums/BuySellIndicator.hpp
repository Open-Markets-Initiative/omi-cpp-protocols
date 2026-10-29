#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// The type of order being added.
enum class BuySellIndicator : char {
    BuyOrder = 'B',  // Buy Order
    SellOrder = 'S', // Sell Order
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BuySellIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BuySellIndicator value);

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
