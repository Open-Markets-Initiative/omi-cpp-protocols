#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// negotiationRejectCode
enum class NegotiationRejectCode : std::uint8_t {
    Unspecified = 0,                  // Unspecified
    Credentials = 1,                  // Credentials
    FlowtypeNotSupported = 2,         // Flowtype Not Supported
    AlreadyNegotiated = 3,            // Already Negotiated
    SessionBlocked = 4,               // Session Blocked
    InvalidSessionid = 5,             // Invalid Sessionid
    InvalidSessionverid = 6,          // Invalid Sessionverid
    InvalidTimestamp = 7,             // Invalid Timestamp
    InvalidFirm = 8,                  // Invalid Firm
    NegotiateNotAllowed = 20,         // Negotiate Not Allowed
    DuplicateSessionConnection = 21,  // Duplicate Session Connection
    AuthenticationInProgress = 22,    // Authentication In Progress
    ProtocolVersionNotSupported = 23, // Protocol Version Not Supported
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(NegotiationRejectCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, NegotiationRejectCode value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
