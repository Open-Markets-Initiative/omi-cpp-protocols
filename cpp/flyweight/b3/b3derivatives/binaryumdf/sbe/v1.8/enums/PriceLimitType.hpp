#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// priceLimitType
enum class PriceLimitType : std::uint8_t {
    PriceUnit = 0,  // Price Unit
    Ticks = 1,      // Ticks
    Percentage = 2, // Percentage
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PriceLimitType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PriceLimitType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
