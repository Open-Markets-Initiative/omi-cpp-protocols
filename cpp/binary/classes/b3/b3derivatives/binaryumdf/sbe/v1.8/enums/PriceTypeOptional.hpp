#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// priceType
enum class PriceTypeOptional : std::uint8_t {
    Percentage = 1,  // Percentage
    Pu = 2,          // Pu
    FixedAmount = 3, // Fixed Amount
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceTypeOptional value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceTypeOptional value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
