#include "ErrorCodes.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

std::string_view to_string(ErrorCodes value) {
    switch (value) {
        case ErrorCodes::HmacReject: return "Hmac Reject";
        case ErrorCodes::InvalidValue: return "Invalid Value";
        case ErrorCodes::SlowConnection: return "Slow Connection";
        case ErrorCodes::Other: return "Other";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ErrorCodes value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_8
