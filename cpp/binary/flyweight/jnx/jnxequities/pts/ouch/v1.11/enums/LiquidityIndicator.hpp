#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Identifies whether this would-be trade was a result of a liquidity provider providing or
// liquidity taker taking the liquidity
enum class LiquidityIndicator : char {
    Added = 'A',   // Added
    Removed = 'R', // Removed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LiquidityIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LiquidityIndicator value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
