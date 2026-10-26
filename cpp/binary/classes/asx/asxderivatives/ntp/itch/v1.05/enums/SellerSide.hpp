#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Type of order
enum class SellerSide : char {
    Sell = 'S', // Sell
    Buy = 'B',  // Buy
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SellerSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SellerSide value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
