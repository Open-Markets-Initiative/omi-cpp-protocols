#include "GovernanceIndicator.hpp"

namespace b3::b3derivatives::binaryumdf::sbe::v1_7 {

std::string_view to_string(GovernanceIndicator value) {
    switch (value) {
        case GovernanceIndicator::No: return "No";
        case GovernanceIndicator::N1: return "N 1";
        case GovernanceIndicator::N2: return "N 2";
        case GovernanceIndicator::Nm: return "Nm";
        case GovernanceIndicator::Ma: return "Ma";
        case GovernanceIndicator::Mb: return "Mb";
        case GovernanceIndicator::M2: return "M 2";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, GovernanceIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_7
