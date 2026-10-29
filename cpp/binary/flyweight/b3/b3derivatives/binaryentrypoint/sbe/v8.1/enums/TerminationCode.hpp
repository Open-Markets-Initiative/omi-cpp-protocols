#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// terminationCode
enum class TerminationCode : std::uint8_t {
    Unspecified = 0,                  // Unspecified
    Finished = 1,                     // Finished
    Unnegotiated = 2,                 // Unnegotiated
    NotEstablished = 3,               // Not Established
    SessionBlocked = 4,               // Session Blocked
    NegotiationInProgress = 5,        // Negotiation In Progress
    EstablishInProgress = 6,          // Establish In Progress
    KeepaliveIntervalLapsed = 10,     // Keepalive Interval Lapsed
    InvalidSessionid = 11,            // Invalid Sessionid
    InvalidSessionverid = 12,         // Invalid Sessionverid
    InvalidTimestamp = 13,            // Invalid Timestamp
    InvalidNextseqno = 14,            // Invalid Nextseqno
    UnrecognizedMessage = 15,         // Unrecognized Message
    InvalidSofh = 16,                 // Invalid Sofh
    DecodingError = 17,               // Decoding Error
    TerminateNotAllowed = 20,         // Terminate Not Allowed
    TerminateInProgress = 21,         // Terminate In Progress
    ProtocolVersionNotSupported = 23, // Protocol Version Not Supported
    BackupTakeoverInProgress = 30,    // Backup Takeover In Progress
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TerminationCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TerminationCode value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
