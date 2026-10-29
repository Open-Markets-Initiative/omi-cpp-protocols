#include "MassCancelRestatementReason.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

std::string_view to_string(MassCancelRestatementReason value) {
    switch (value) {
        case MassCancelRestatementReason::OrderMassActionFromClientRequest: return "Order Mass Action From Client Request";
        case MassCancelRestatementReason::MassCancelOrderDueToOperationalErrorRequest: return "Mass Cancel Order Due To Operational Error Request";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MassCancelRestatementReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
