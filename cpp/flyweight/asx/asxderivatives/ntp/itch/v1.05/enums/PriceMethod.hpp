#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Pricing method
enum class PriceMethod : std::uint8_t {
    NetPrice = 0,        // Net Price
    YieldDifference = 2, // Yield Difference
    Individual = 3,      // Individual
    AveragePrice = 4,    // Average Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceMethod value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceMethod value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
