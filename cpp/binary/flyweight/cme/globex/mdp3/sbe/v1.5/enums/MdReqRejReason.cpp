#include "MdReqRejReason.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

std::string_view to_string(MdReqRejReason value) {
    switch (value) {
        case MdReqRejReason::UnknownSecurity: return "Unknown Security";
        case MdReqRejReason::UnknownMessage: return "Unknown Message";
        case MdReqRejReason::UnsupportedScope: return "Unsupported Scope";
        case MdReqRejReason::Other: return "Other";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MdReqRejReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_5
