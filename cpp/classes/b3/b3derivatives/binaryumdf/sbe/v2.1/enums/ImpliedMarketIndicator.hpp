#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_1 {

// impliedMarketIndicator
enum class ImpliedMarketIndicator : std::uint8_t {
    NotImplied = 0, // Not Implied
    Implied = 1,    // Implied
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ImpliedMarketIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ImpliedMarketIndicator value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_1
