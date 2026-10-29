#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// The side of this individual leg (multileg security). See Side (54) field for description and
// values.
enum class LegSide : char {
    Buy = '1',  // Buy
    Sell = '2', // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSide value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
