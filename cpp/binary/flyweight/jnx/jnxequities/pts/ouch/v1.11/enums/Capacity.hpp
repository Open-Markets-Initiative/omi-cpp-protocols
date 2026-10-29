#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Capacity of firm placing order
enum class Capacity : char {
    Agency = 'A',    // Agency
    Principal = 'P', // Principal
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Capacity value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Capacity value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
