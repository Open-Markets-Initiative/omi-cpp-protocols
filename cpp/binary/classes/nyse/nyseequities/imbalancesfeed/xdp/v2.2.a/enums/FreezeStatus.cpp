#include "FreezeStatus.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

std::string_view to_string(FreezeStatus value) {
    switch (value) {
        case FreezeStatus::NoImbalanceFreeze: return "No Imbalance Freeze";
        case FreezeStatus::ImbalanceFreeze: return "Imbalance Freeze";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FreezeStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
