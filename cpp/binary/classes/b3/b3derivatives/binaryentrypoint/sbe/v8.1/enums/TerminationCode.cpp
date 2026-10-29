#include "TerminationCode.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(TerminationCode value) {
    switch (value) {
        case TerminationCode::Unspecified: return "Unspecified";
        case TerminationCode::Finished: return "Finished";
        case TerminationCode::Unnegotiated: return "Unnegotiated";
        case TerminationCode::NotEstablished: return "Not Established";
        case TerminationCode::SessionBlocked: return "Session Blocked";
        case TerminationCode::NegotiationInProgress: return "Negotiation In Progress";
        case TerminationCode::EstablishInProgress: return "Establish In Progress";
        case TerminationCode::KeepaliveIntervalLapsed: return "Keepalive Interval Lapsed";
        case TerminationCode::InvalidSessionid: return "Invalid Sessionid";
        case TerminationCode::InvalidSessionverid: return "Invalid Sessionverid";
        case TerminationCode::InvalidTimestamp: return "Invalid Timestamp";
        case TerminationCode::InvalidNextseqno: return "Invalid Nextseqno";
        case TerminationCode::UnrecognizedMessage: return "Unrecognized Message";
        case TerminationCode::InvalidSofh: return "Invalid Sofh";
        case TerminationCode::DecodingError: return "Decoding Error";
        case TerminationCode::TerminateNotAllowed: return "Terminate Not Allowed";
        case TerminationCode::TerminateInProgress: return "Terminate In Progress";
        case TerminationCode::ProtocolVersionNotSupported: return "Protocol Version Not Supported";
        case TerminationCode::BackupTakeoverInProgress: return "Backup Takeover In Progress";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TerminationCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
