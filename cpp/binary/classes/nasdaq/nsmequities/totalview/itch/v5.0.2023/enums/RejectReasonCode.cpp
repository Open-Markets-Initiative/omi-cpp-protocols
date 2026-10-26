#include "RejectReasonCode.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(RejectReasonCode value) {
    switch (value) {
        case RejectReasonCode::NotAuthorized: return "Not Authorized";
        case RejectReasonCode::SessionNotAvailable: return "Session Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RejectReasonCode value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
