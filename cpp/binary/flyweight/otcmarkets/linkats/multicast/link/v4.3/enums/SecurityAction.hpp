#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Security action indicator.
enum class SecurityAction : std::uint8_t {
    Update = 1, // Update
    Add = 2,    // Add
    Delete = 3, // Delete
    Spin = 4,   // Spin
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityAction value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
