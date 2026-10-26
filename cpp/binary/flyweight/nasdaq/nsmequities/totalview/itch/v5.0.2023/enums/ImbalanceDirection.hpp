#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// The market side of the order imbalance
enum class ImbalanceDirection : char {
    Buy = 'B',                // Buy
    Sell = 'S',               // Sell
    None = 'N',               // None
    InsufficientOrders = 'O', // Insufficient Orders
    Paused = 'P',             // Paused
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ImbalanceDirection value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ImbalanceDirection value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
