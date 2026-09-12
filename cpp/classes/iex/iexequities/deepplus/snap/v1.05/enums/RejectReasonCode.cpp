#include "RejectReasonCode.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

std::string_view to_string(RejectReasonCode value) {
    switch (value) {
        case RejectReasonCode::AuthenticationFailure: return "Authentication Failure";
        case RejectReasonCode::IncorrectChannelId: return "Incorrect Channel Id";
        case RejectReasonCode::SnapshotRequestAlreadyActive: return "Snapshot Request Already Active";
        case RejectReasonCode::QuotaExceeded: return "Quota Exceeded";
        case RejectReasonCode::SnapshotNotYetAvailable: return "Snapshot Not Yet Available";
        case RejectReasonCode::IncorrectSessionId: return "Incorrect Session Id";
        case RejectReasonCode::UnknownMessage: return "Unknown Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RejectReasonCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deepplus::snap::v1_05
