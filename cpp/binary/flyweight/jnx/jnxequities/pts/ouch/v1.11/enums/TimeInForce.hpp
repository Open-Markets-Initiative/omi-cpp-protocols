#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// How long the order remains in effect
enum class TimeInForce : std::uint32_t {
    Immediate = 0, // Immediate
    Day = 99999,   // Day
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TimeInForce value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TimeInForce value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
