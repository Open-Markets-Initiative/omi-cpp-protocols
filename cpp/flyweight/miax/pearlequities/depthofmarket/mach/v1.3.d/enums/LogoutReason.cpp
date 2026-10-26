#include "LogoutReason.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(LogoutReason value) {
    switch (value) {
        case LogoutReason::GracefulLogout: return "Graceful Logout";
        case LogoutReason::BadPacket: return "Bad Packet";
        case LogoutReason::TimedOut: return "Timed Out";
        case LogoutReason::ApplicationTerminatingConnection: return "Application Terminating Connection";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LogoutReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
