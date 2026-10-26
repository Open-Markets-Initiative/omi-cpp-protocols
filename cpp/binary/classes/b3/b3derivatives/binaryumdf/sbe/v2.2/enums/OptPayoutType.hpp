#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_2 {

// optPayoutType
enum class OptPayoutType : std::uint8_t {
    Vanilla = 1, // Vanilla
    Capped = 2,  // Capped
    Binary = 3,  // Binary
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OptPayoutType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OptPayoutType value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_2
