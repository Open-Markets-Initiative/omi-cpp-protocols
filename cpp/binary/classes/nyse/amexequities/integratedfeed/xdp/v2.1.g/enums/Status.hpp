#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// The reason why the request was rejected.
enum class Status : char {
    MessageWasAccepted = '0',              // Message Was Accepted
    RejectedDueToAnInvalidSourceId = '1',  // Rejected Due To An Invalid Source Id
    InvalidSequenceRange = '2',            // Invalid Sequence Range
    MaximumSequenceRange = '3',            // Maximum Sequence Range
    MaximumRequestInADay = '4',            // Maximum Request In A Day
    MaximumRefreshRequestsInADay = '5',    // Maximum Refresh Requests In A Day
    OldSeqNumTtl = '6',                    // Old Seq Num Ttl
    InvalidChannelId = '7',                // Invalid Channel Id
    InvalidProductId = '8',                // Invalid Product Id
    InvalidMsgTypeOrMsgSizeMismatch = '9', // Invalid Msg Type Or Msg Size Mismatch
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Status value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Status value);

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
