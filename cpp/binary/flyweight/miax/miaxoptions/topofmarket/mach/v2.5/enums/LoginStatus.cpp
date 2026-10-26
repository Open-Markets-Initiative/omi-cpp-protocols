#include "LoginStatus.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(LoginStatus value) {
    switch (value) {
        case LoginStatus::Successful: return "Successful";
        case LoginStatus::InvalidTradingSessionRequested: return "Invalid Trading Session Requested";
        case LoginStatus::NoActiveTradingSessionExists: return "No Active Trading Session Exists";
        case LoginStatus::Rejected: return "Rejected";
        case LoginStatus::InvalidStartSequenceNumberRequested: return "Invalid Start Sequence Number Requested";
        case LoginStatus::IncompatibleSessionProtocolVersion: return "Incompatible Session Protocol Version";
        case LoginStatus::IncompatibleApplicationProtocolVersion: return "Incompatible Application Protocol Version";
        case LoginStatus::RequestRejectedBecauseClientAlreadyLoggedIn: return "Request Rejected Because Client Already Logged In";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LoginStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
