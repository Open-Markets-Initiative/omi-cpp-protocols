#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// The market side of the order imbalance
enum class ImbalanceDirection : char {
    BuyImbalance = 'B',                  // Buy Imbalance
    SellImbalance = 'S',                 // Sell Imbalance
    NoImbalance = 'N',                   // No Imbalance
    InsufficientOrdersToCalculate = 'O', // Insufficient Orders To Calculate
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ImbalanceDirection value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ImbalanceDirection value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
