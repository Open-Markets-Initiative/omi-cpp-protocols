#include "UnpairedSide.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::string_view to_string(UnpairedSide value) {
    switch (value) {
        case UnpairedSide::NotApplicable: return "Not Applicable";
        case UnpairedSide::BuySide: return "Buy Side";
        case UnpairedSide::SellSide: return "Sell Side";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UnpairedSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
