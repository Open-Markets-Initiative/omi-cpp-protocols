#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace asx::asxderivatives::ntp::itch::v1_05 {

// Indicates the current session state for the contract as per
enum class SessionState : char {
    PreOpen = 'P',        // Pre Open
    Opened = 'O',         // Opened
    RegulatoryHalt = 'R', // Regulatory Halt
    Halted = 'H',         // Halted
    Closed = 'C',         // Closed
    Maintenance = 'M',    // Maintenance
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SessionState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SessionState value);

} // namespace asx::asxderivatives::ntp::itch::v1_05
