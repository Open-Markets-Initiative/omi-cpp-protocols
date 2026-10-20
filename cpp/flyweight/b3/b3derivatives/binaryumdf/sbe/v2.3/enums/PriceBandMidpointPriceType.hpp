#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// priceBandMidpointPriceType
enum class PriceBandMidpointPriceType : std::uint8_t {
    LastTradedPrice = 0,        // Last Traded Price
    ComplementaryLastPrice = 1, // Complementary Last Price
    TheoreticalPrice = 2,       // Theoretical Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceBandMidpointPriceType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceBandMidpointPriceType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
