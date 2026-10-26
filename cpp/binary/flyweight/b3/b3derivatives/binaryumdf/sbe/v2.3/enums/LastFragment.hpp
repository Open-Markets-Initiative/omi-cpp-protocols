#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// lastFragment
enum class LastFragment : std::uint8_t {
    FalseValue = 0, // False Value
    TrueValue = 1,  // True Value
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LastFragment value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LastFragment value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
