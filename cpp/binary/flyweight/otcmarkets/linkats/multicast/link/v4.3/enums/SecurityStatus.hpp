#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Security status.
enum class SecurityStatus : char {
    Active = 'A',       // Active
    QuoteOnly = 'Q',    // Quote Only
    Suspended = 'S',    // Suspended
    Halted = 'H',       // Halted
    InternalHalt = 'I', // Internal Halt
    Revoked = 'R',      // Revoked
    Deleted = 'D',      // Deleted
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatus value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
