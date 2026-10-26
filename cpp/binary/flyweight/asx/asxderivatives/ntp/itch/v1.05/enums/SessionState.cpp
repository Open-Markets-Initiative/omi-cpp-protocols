#include "SessionState.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(SessionState value) {
    switch (value) {
        case SessionState::PreOpen: return "Pre Open";
        case SessionState::Opened: return "Opened";
        case SessionState::RegulatoryHalt: return "Regulatory Halt";
        case SessionState::Halted: return "Halted";
        case SessionState::Closed: return "Closed";
        case SessionState::Maintenance: return "Maintenance";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SessionState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
