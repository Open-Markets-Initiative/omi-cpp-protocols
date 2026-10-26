#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

// Login Status
enum class LoginStatus : char {
    Successful = ' ',                                  // Successful
    InvalidTradingSessionRequested = 'S',              // Invalid Trading Session Requested
    NoActiveTradingSessionExists = 'U',                // No Active Trading Session Exists
    Rejected = 'X',                                    // Rejected
    InvalidStartSequenceNumberRequested = 'N',         // Invalid Start Sequence Number Requested
    IncompatibleSessionProtocolVersion = 'I',          // Incompatible Session Protocol Version
    IncompatibleApplicationProtocolVersion = 'A',      // Incompatible Application Protocol Version
    RequestRejectedBecauseClientAlreadyLoggedIn = 'L', // Request Rejected Because Client Already Logged In
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LoginStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LoginStatus value);

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
