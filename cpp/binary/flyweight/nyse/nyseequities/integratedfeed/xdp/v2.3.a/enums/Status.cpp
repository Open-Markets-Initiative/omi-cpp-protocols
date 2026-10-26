#include "Status.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::string_view to_string(Status value) {
    switch (value) {
        case Status::MessageWasAccepted: return "Message Was Accepted";
        case Status::RejectedDueToAnInvalidSourceId: return "Rejected Due To An Invalid Source Id";
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

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
