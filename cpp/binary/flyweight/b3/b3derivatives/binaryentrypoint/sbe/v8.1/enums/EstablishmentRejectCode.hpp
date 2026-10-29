#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// establishmentRejectCode
enum class EstablishmentRejectCode : std::uint8_t {
    Unspecified = 0,                  // Unspecified
    Credentials = 1,                  // Credentials
    Unnegotiated = 2,                 // Unnegotiated
    AlreadyEstablished = 3,           // Already Established
    SessionBlocked = 4,               // Session Blocked
    InvalidSessionid = 5,             // Invalid Sessionid
    InvalidSessionverid = 6,          // Invalid Sessionverid
    InvalidTimestamp = 7,             // Invalid Timestamp
    InvalidKeepaliveInterval = 8,     // Invalid Keepalive Interval
    InvalidNextseqno = 9,             // Invalid Nextseqno
    EstablishAttemptsExceeded = 10,   // Establish Attempts Exceeded
    EstablishNotAllowed = 20,         // Establish Not Allowed
    DuplicateSessionConnection = 21,  // Duplicate Session Connection
    AuthenticationInProgress = 22,    // Authentication In Progress
    ProtocolVersionNotSupported = 23, // Protocol Version Not Supported
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(EstablishmentRejectCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, EstablishmentRejectCode value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
