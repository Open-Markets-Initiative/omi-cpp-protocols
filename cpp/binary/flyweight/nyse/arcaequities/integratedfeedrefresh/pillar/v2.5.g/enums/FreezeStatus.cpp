#include "FreezeStatus.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

std::string_view to_string(FreezeStatus value) {
    switch (value) {
        case FreezeStatus::ImbalanceFreezeNotInEffect: return "Imbalance Freeze Not In Effect";
        case FreezeStatus::ImbalanceFreezeIsInEffect: return "Imbalance Freeze Is In Effect";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FreezeStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g
