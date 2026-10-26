#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// settlPriceType
enum class SettlPriceType : std::uint8_t {
    Final = 1,       // Final
    Theoretical = 2, // Theoretical
    Updated = 3,     // Updated
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SettlPriceType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SettlPriceType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
