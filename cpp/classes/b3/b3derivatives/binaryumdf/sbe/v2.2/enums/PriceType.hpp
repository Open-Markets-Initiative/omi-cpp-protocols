#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// priceType
enum class PriceType : std::uint8_t {
    Percentage = 1,  // Percentage
    Pu = 2,          // Pu
    FixedAmount = 3, // Fixed Amount
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
