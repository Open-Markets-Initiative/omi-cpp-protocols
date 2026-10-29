#include "MassActionType.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

std::string_view to_string(MassActionType value) {
    switch (value) {
        case MassActionType::ReleaseOrdersFromSuspension: return "Release Orders From Suspension";
        case MassActionType::CancelOrders: return "Cancel Orders";
        case MassActionType::CancelAndSuspendOrders: return "Cancel And Suspend Orders";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MassActionType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
