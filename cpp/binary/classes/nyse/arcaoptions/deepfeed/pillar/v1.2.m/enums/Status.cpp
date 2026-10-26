#include "Status.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(Status value) {
    switch (value) {
        case Status::MessageWasAccepted: return "Message Was Accepted";
        case Status::RejectedDueToAnInvalidSourceId: return "Rejected Due To An Invalid Source Id";
        case Status::RejectedDueToMaximumSequenceRange: return "Rejected Due To Maximum Sequence Range";
        case Status::RejectedDueToMaximumRequestInADay: return "Rejected Due To Maximum Request In A Day";
        case Status::RejectedDueToMaximumNumberOfRefreshRequestsInADay: return "Rejected Due To Maximum Number Of Refresh Requests In A Day";
        case Status::RejectedRequestMessageSeqNumTtlIsTooOld: return "Rejected Request Message Seq Num Ttl Is Too Old";
        case Status::RejectedDueToAnInvalidChannelId: return "Rejected Due To An Invalid Channel Id";
        case Status::RejectedDueToAnInvalidProductId: return "Rejected Due To An Invalid Product Id";
        case Status::RejectedDueToInvalidMsgTypeOrMismatchBetweenMsgTypeAndMsgSize: return "Rejected Due To Invalid Msg Type Or Mismatch Between Msg Type And Msg Size";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Status value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
