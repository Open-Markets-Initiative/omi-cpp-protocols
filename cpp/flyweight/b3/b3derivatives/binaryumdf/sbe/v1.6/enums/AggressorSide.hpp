#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_6 {

// aggressorSide
enum class AggressorSide : std::uint8_t {
    NoAggressor = 0, // No Aggressor
    Buy = 1,         // Buy
    Sell = 2,        // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AggressorSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AggressorSide value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_6
