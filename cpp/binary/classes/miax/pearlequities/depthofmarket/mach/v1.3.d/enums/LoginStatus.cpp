// Miax.PearlEquities.DepthOfMarket.Mach.v1.3.d: enums/LoginStatus.cpp
#include "LoginStatus.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(LoginStatus value) {
    switch (value) {
        case LoginStatus::Successful: return "Successful";
        case LoginStatus::InvalidTradingSessionRequested: return "Invalid Trading Session Requested";
        case LoginStatus::InvalidStartSequenceNumberRequested: return "Invalid Start Sequence Number Requested";
        case LoginStatus::NoActiveTradingSessionExists: return "No Active Trading Session Exists";
        case LoginStatus::Rejected: return "Rejected";
        case LoginStatus::IncompatibleSessionProtocolVersion: return "Incompatible Session Protocol Version";
        case LoginStatus::IncompatibleApplicationProtocolVersion: return "Incompatible Application Protocol Version";
        case LoginStatus::InvalidNumberOfMatchingEnginesSpecifiedInLoginRequest: return "Invalid Number Of Matching Engines Specified In Login Request";
        case LoginStatus::RequestRejectedBecauseClientAlreadyLoggedIn: return "Request Rejected Because Client Already Logged In";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LoginStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
