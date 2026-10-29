#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// System event code
enum class SystemEvent : char {
    StartOfDay = 'S', // Start Of Day
    EndOfDay = 'E',   // End Of Day
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SystemEvent value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SystemEvent value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
