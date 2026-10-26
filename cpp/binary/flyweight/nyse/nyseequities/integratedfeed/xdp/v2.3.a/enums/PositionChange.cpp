#include "PositionChange.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::string_view to_string(PositionChange value) {
    switch (value) {
        case PositionChange::Kept: return "Kept";
        case PositionChange::Lost: return "Lost";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, PositionChange value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
