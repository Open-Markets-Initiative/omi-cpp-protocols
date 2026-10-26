#include "SecurityMassStatus.hpp"

namespace eurex::t7::eobi::fbe::v15_0 {

std::string_view to_string(SecurityMassStatus value) {
    switch (value) {
        case SecurityMassStatus::Active: return "Active";
        case SecurityMassStatus::Inactive: return "Inactive";
        case SecurityMassStatus::Expired: return "Expired";
        case SecurityMassStatus::KnockedOut: return "Knocked Out";
        case SecurityMassStatus::KnockOutRevoked: return "Knock Out Revoked";
        case SecurityMassStatus::Suspended: return "Suspended";
        case SecurityMassStatus::PendingDeletion: return "Pending Deletion";
        case SecurityMassStatus::KnockedOutAndSuspended: return "Knocked Out And Suspended";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityMassStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace eurex::t7::eobi::fbe::v15_0
