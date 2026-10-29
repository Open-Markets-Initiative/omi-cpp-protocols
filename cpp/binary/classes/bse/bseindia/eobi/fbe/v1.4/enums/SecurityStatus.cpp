#include "SecurityStatus.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

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

} // namespace bse::bseindia::eobi::fbe::v1_4
