#include "TesSecurityStatus.hpp"

namespace eurex::t7::eobi::fbe::v13_0 {

std::string_view to_string(TesSecurityStatus value) {
    switch (value) {
        case TesSecurityStatus::Active: return "Active";
        case TesSecurityStatus::Inactive: return "Inactive";
        case TesSecurityStatus::Expired: return "Expired";
        case TesSecurityStatus::Suspended: return "Suspended";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TesSecurityStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v13_0
