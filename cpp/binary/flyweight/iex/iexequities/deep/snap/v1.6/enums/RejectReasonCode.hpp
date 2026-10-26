#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::deep::snap::v1_6 {

// Reason the Snapshot Request was rejected
enum class RejectReasonCode : char {
    AuthenticationFailure = 'A',        // Authentication Failure
    IncorrectChannelId = 'C',           // Incorrect Channel Id
    SnapshotRequestAlreadyActive = 'E', // Snapshot Request Already Active
    QuotaExceeded = 'Q',                // Quota Exceeded
    SnapshotNotYetAvailable = 'R',      // Snapshot Not Yet Available
    IncorrectSessionId = 'S',           // Incorrect Session Id
    UnknownMessage = 'U',               // Unknown Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RejectReasonCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RejectReasonCode value);

} // namespace iex::iexequities::deep::snap::v1_6
