#include "TesSecurityMassStatus.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(TesSecurityMassStatus value) {
    switch (value) {
        case TesSecurityMassStatus::Active: return "Active";
        case TesSecurityMassStatus::Inactive: return "Inactive";
        case TesSecurityMassStatus::Expired: return "Expired";
        case TesSecurityMassStatus::Suspended: return "Suspended";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TesSecurityMassStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
