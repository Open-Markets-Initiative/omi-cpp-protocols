#include "NegotiationRejectCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(NegotiationRejectCode value) {
    switch (value) {
        case NegotiationRejectCode::Unspecified: return "Unspecified";
        case NegotiationRejectCode::Credentials: return "Credentials";
        case NegotiationRejectCode::FlowtypeNotSupported: return "Flowtype Not Supported";
        case NegotiationRejectCode::AlreadyNegotiated: return "Already Negotiated";
        case NegotiationRejectCode::SessionBlocked: return "Session Blocked";
        case NegotiationRejectCode::InvalidSessionid: return "Invalid Sessionid";
        case NegotiationRejectCode::InvalidSessionverid: return "Invalid Sessionverid";
        case NegotiationRejectCode::InvalidTimestamp: return "Invalid Timestamp";
        case NegotiationRejectCode::InvalidFirm: return "Invalid Firm";
        case NegotiationRejectCode::NegotiateNotAllowed: return "Negotiate Not Allowed";
        case NegotiationRejectCode::DuplicateSessionConnection: return "Duplicate Session Connection";
        case NegotiationRejectCode::AuthenticationInProgress: return "Authentication In Progress";
        case NegotiationRejectCode::ProtocolVersionNotSupported: return "Protocol Version Not Supported";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, NegotiationRejectCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
