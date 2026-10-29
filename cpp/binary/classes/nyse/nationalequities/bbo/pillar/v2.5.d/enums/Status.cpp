#include "Status.hpp"

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

std::string_view to_string(Status value) {
    switch (value) {
        case Status::MessageWasAccepted: return "Message Was Accepted";
        case Status::RejectedDueToAnInvalidSourceId: return "Rejected Due To An Invalid Source Id";
        case Status::RejectedDueToMaximumSequenceRangeSeeThresholdLimits: return "Rejected Due To Maximum Sequence Range See Threshold Limits";
        case Status::RejectedDueToMaximumRequestInADay: return "Rejected Due To Maximum Request In A Day";
        case Status::RejectedDueToMaximumNumberOfRefreshRequestsInADay: return "Rejected Due To Maximum Number Of Refresh Requests In A Day";
        case Status::RejectedRequestMessageSeqNumTtlTimeToLiveIsTooOldUseRefreshToRecoverCurrentStateIfNecessary: return "Rejected Request Message Seq Num Ttl Time To Live Is Too Old Use Refresh To Recover Current State If Necessary";
        case Status::RejectedDueToAnInvalidChannelId: return "Rejected Due To An Invalid Channel Id";
        case Status::RejectedDueToAnInvalidProductId: return "Rejected Due To An Invalid Product Id";
        case Status::RejectedDueTo1InvalidMsgTypeOr2MismatchBetweenMsgTypeAndMsgSize: return "Rejected Due To 1 Invalid Msg Type Or 2 Mismatch Between Msg Type And Msg Size";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Status value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nationalequities::bbo::pillar::v2_5_d
