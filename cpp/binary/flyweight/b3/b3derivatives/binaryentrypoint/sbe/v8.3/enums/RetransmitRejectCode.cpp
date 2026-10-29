#include "RetransmitRejectCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(RetransmitRejectCode value) {
    switch (value) {
        case RetransmitRejectCode::OutOfRange: return "Out Of Range";
        case RetransmitRejectCode::InvalidSession: return "Invalid Session";
        case RetransmitRejectCode::RequestLimitExceeded: return "Request Limit Exceeded";
        case RetransmitRejectCode::RetransmitInProgress: return "Retransmit In Progress";
        case RetransmitRejectCode::InvalidTimestamp: return "Invalid Timestamp";
        case RetransmitRejectCode::InvalidFromseqno: return "Invalid Fromseqno";
        case RetransmitRejectCode::InvalidCount: return "Invalid Count";
        case RetransmitRejectCode::ThrottleReject: return "Throttle Reject";
        case RetransmitRejectCode::SystemBusy: return "System Busy";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RetransmitRejectCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
