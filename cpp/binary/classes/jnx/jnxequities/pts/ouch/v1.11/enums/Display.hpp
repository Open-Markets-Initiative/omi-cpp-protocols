#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Order handling instruction
enum class Display : char {
    Unused = ' ',   // Unused
    PostOnly = 'P', // Post Only
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Display value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Display value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
