#include "MassActionRejectReason.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(MassActionRejectReason value) {
    switch (value) {
        case MassActionRejectReason::MassActionNotSupported: return "Mass Action Not Supported";
        case MassActionRejectReason::InvalidOrUnknownMarketSegment: return "Invalid Or Unknown Market Segment";
        case MassActionRejectReason::Other: return "Other";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MassActionRejectReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
