#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

// Logout Request Reason
enum class LogoutReason : char {
    GracefulLogout = ' ',                   // Graceful Logout
    BadPacket = 'B',                        // Bad Packet
    TimedOut = 'L',                         // Timed Out
    ApplicationTerminatingConnection = 'A', // Application Terminating Connection
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LogoutReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LogoutReason value);

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
