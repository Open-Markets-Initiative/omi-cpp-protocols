#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::trades::pillar::v2_6 {

// The reason why the request was rejected.
enum class Status : char {
    MessageWasAccepted = '0',                                                                          // Message Was Accepted
    RejectedDueToAnInvalidSourceId = '1',                                                              // Rejected Due To An Invalid Source Id
    RejectedDueToMaximumSequenceRangeSeeThresholdLimits = '3',                                         // Rejected Due To Maximum Sequence Range See Threshold Limits
    RejectedDueToMaximumRequestInADay = '4',                                                           // Rejected Due To Maximum Request In A Day
    RejectedDueToMaximumNumberOfRefreshRequestsInADay = '5',                                           // Rejected Due To Maximum Number Of Refresh Requests In A Day
    RejectedRequestMessageSeqNumTtlTimeToLiveIsTooOldUseRefreshToRecoverCurrentStateIfNecessary = '6', // Rejected Request Message Seq Num Ttl Time To Live Is Too Old Use Refresh To Recover Current State If Necessary
    RejectedDueToAnInvalidChannelId = '7',                                                             // Rejected Due To An Invalid Channel Id
    RejectedDueToAnInvalidProductId = '8',                                                             // Rejected Due To An Invalid Product Id
    RejectedDueTo1InvalidMsgTypeOr2MismatchBetweenMsgTypeAndMsgSize = '9',                             // Rejected Due To 1 Invalid Msg Type Or 2 Mismatch Between Msg Type And Msg Size
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Status value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Status value);

} // namespace nyse::nationalequities::trades::pillar::v2_6
