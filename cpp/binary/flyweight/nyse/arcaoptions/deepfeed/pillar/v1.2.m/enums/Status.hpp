#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// The reason why the request was rejected.
enum class Status : char {
    MessageWasAccepted = '0',                                            // Message Was Accepted
    RejectedDueToAnInvalidSourceId = '1',                                // Rejected Due To An Invalid Source Id
    RejectedDueToMaximumSequenceRange = '3',                             // Rejected Due To Maximum Sequence Range
    RejectedDueToMaximumRequestInADay = '4',                             // Rejected Due To Maximum Request In A Day
    RejectedDueToMaximumNumberOfRefreshRequestsInADay = '5',             // Rejected Due To Maximum Number Of Refresh Requests In A Day
    RejectedRequestMessageSeqNumTtlIsTooOld = '6',                       // Rejected Request Message Seq Num Ttl Is Too Old
    RejectedDueToAnInvalidChannelId = '7',                               // Rejected Due To An Invalid Channel Id
    RejectedDueToAnInvalidProductId = '8',                               // Rejected Due To An Invalid Product Id
    RejectedDueToInvalidMsgTypeOrMismatchBetweenMsgTypeAndMsgSize = '9', // Rejected Due To Invalid Msg Type Or Mismatch Between Msg Type And Msg Size
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Status value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Status value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
