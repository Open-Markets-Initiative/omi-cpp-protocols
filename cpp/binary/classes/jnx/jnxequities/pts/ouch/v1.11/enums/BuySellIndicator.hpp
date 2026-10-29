#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Side of order
enum class BuySellIndicator : char {
    Buy = 'B',             // Buy
    Sell = 'S',            // Sell
    ShortSell = 'T',       // Short Sell
    ShortSellExempt = 'E', // Short Sell Exempt
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BuySellIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BuySellIndicator value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
