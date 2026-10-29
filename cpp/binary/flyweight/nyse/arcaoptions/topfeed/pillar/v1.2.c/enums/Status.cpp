#include "Status.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(Status value) {
    switch (value) {
        case Status::Accepted: return "Accepted";
        case Status::Rejected: return "Rejected";
        case Status::InvalidSequenceRange: return "Invalid Sequence Range";
        case Status::MaximumSequenceRange: return "Maximum Sequence Range";
        case Status::MaximumRequestInADay: return "Maximum Request In A Day";
        case Status::MaximumRefreshRequestsInADay: return "Maximum Refresh Requests In A Day";
        case Status::OldSeqNumTtl: return "Old Seq Num Ttl";
        case Status::InvalidChannelId: return "Invalid Channel Id";
        case Status::InvalidProductId: return "Invalid Product Id";
        case Status::InvalidMsgTypeOrMsgSize: return "Invalid Msg Type Or Msg Size";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, Status value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
