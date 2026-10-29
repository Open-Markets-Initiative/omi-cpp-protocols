#include "SecurityStatus.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

std::string_view to_string(SecurityStatus value) {
    switch (value) {
        case SecurityStatus::Active: return "Active";
        case SecurityStatus::Inactive: return "Inactive";
        case SecurityStatus::Expired: return "Expired";
        case SecurityStatus::Suspended: return "Suspended";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v6_0
