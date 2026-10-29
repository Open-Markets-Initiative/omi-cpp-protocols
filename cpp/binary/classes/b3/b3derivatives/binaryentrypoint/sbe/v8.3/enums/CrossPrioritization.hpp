#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// crossPrioritization
enum class CrossPrioritization : std::uint8_t {
    None = 0,                  // None
    BuySideIsPrioritized = 1,  // Buy Side Is Prioritized
    SellSideIsPrioritized = 2, // Sell Side Is Prioritized
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossPrioritization value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossPrioritization value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
