#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v6_0 {

enum class ProductComplex : std::uint8_t {
    StandardOptionStrategy = 2,    // Standard Option Strategy
    NonStandardOptionStrategy = 3, // Non Standard Option Strategy
    VolatilityStrategy = 4,        // Volatility Strategy
    FuturesSpread = 5,             // Futures Spread
    InterProductSpread = 6,        // Inter Product Spread
    StandardFuturesStrategy = 7,   // Standard Futures Strategy
    PackAndBundle = 8,             // Pack And Bundle
    Strip = 9,                     // Strip
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ProductComplex value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ProductComplex value);

} // namespace eurex::t7::eobi::fbe::v6_0
