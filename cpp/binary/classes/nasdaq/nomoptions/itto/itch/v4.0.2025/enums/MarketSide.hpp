#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The type of order being added.
enum class MarketSide : char {
    Buy = 'B',  // Buy
    Sell = 'S', // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketSide value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
