#include "PositionChange.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

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

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
