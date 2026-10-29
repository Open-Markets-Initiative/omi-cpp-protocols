#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

// The reason why the request was rejected.
enum class Status : char {
    Accepted = '0',                     // Accepted
    Rejected = '1',                     // Rejected
    InvalidSequenceRange = '2',         // Invalid Sequence Range
    MaximumSequenceRange = '3',         // Maximum Sequence Range
    MaximumRequestInADay = '4',         // Maximum Request In A Day
    MaximumRefreshRequestsInADay = '5', // Maximum Refresh Requests In A Day
    OldSeqNumTtl = '6',                 // Old Seq Num Ttl
    InvalidChannelId = '7',             // Invalid Channel Id
    InvalidProductId = '8',             // Invalid Product Id
    InvalidMsgTypeOrMsgSize = '9',      // Invalid Msg Type Or Msg Size
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Status value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Status value);

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
