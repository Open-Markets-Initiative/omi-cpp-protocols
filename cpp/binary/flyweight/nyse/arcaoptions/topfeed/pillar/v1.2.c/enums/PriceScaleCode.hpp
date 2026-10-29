#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// Specifies placement of the decimal point in price fields for this security.
enum class PriceScaleCode : std::uint8_t {
    LowPricedSecurities = 6,    // Low Priced Securities
    MediumPricedSecurities = 4, // Medium Priced Securities
    HighPricedSecurities = 3,   // High Priced Securities
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceScaleCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceScaleCode value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
