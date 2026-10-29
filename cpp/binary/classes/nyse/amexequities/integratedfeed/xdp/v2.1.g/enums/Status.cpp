#include "Status.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(Status value) {
    switch (value) {
        case Status::MessageWasAccepted: return "Message Was Accepted";
        case Status::RejectedDueToAnInvalidSourceId: return "Rejected Due To An Invalid Source Id";
        case Status::InvalidSequenceRange: return "Invalid Sequence Range";
        case Status::MaximumSequenceRange: return "Maximum Sequence Range";
        case Status::MaximumRequestInADay: return "Maximum Request In A Day";
        case Status::MaximumRefreshRequestsInADay: return "Maximum Refresh Requests In A Day";
        case Status::OldSeqNumTtl: return "Old Seq Num Ttl";
        case Status::InvalidChannelId: return "Invalid Channel Id";
        case Status::InvalidProductId: return "Invalid Product Id";
        case Status::InvalidMsgTypeOrMsgSizeMismatch: return "Invalid Msg Type Or Msg Size Mismatch";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Status value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
