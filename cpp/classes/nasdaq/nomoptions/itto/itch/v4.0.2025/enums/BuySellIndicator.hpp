#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The type of non-display order on the book being matched.
enum class BuySellIndicator : char {
    Buy = 'B',  // Buy
    Sell = 'S', // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BuySellIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BuySellIndicator value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
