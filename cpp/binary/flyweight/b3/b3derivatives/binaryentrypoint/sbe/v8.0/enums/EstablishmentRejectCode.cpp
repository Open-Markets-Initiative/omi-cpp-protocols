#include "EstablishmentRejectCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(EstablishmentRejectCode value) {
    switch (value) {
        case EstablishmentRejectCode::Unspecified: return "Unspecified";
        case EstablishmentRejectCode::Credentials: return "Credentials";
        case EstablishmentRejectCode::Unnegotiated: return "Unnegotiated";
        case EstablishmentRejectCode::AlreadyEstablished: return "Already Established";
        case EstablishmentRejectCode::SessionBlocked: return "Session Blocked";
        case EstablishmentRejectCode::InvalidSessionid: return "Invalid Sessionid";
        case EstablishmentRejectCode::InvalidSessionverid: return "Invalid Sessionverid";
        case EstablishmentRejectCode::InvalidTimestamp: return "Invalid Timestamp";
        case EstablishmentRejectCode::InvalidKeepaliveInterval: return "Invalid Keepalive Interval";
        case EstablishmentRejectCode::InvalidNextseqno: return "Invalid Nextseqno";
        case EstablishmentRejectCode::EstablishAttemptsExceeded: return "Establish Attempts Exceeded";
        case EstablishmentRejectCode::EstablishNotAllowed: return "Establish Not Allowed";
        case EstablishmentRejectCode::DuplicateSessionConnection: return "Duplicate Session Connection";
        case EstablishmentRejectCode::AuthenticationInProgress: return "Authentication In Progress";
        case EstablishmentRejectCode::ProtocolVersionNotSupported: return "Protocol Version Not Supported";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EstablishmentRejectCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
