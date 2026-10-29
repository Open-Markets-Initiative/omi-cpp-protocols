#include "SingleCancelRestatementReason.hpp"

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

std::string_view to_string(SingleCancelRestatementReason value) {
    switch (value) {
        case SingleCancelRestatementReason::CancelOrderDueToOperationalError: return "Cancel Order Due To Operational Error";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SingleCancelRestatementReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
