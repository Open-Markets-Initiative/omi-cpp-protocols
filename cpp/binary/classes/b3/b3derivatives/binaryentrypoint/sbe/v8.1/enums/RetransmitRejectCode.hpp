#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// retransmitRejectCode
enum class RetransmitRejectCode : std::uint8_t {
    OutOfRange = 0,           // Out Of Range
    InvalidSession = 1,       // Invalid Session
    RequestLimitExceeded = 2, // Request Limit Exceeded
    RetransmitInProgress = 3, // Retransmit In Progress
    InvalidTimestamp = 4,     // Invalid Timestamp
    InvalidFromseqno = 5,     // Invalid Fromseqno
    InvalidCount = 9,         // Invalid Count
    ThrottleReject = 10,      // Throttle Reject
    SystemBusy = 11,          // System Busy
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RetransmitRejectCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RetransmitRejectCode value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
