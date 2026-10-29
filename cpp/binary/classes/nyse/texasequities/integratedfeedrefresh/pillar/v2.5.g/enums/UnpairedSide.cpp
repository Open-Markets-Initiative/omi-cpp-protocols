#include "UnpairedSide.hpp"

namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g {

std::string_view to_string(UnpairedSide value) {
    switch (value) {
        case UnpairedSide::BuySide: return "Buy Side";
        case UnpairedSide::SellSide: return "Sell Side";
        case UnpairedSide::NotApplicable: return "Not Applicable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UnpairedSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::texasequities::integratedfeedrefresh::pillar::v2_5_g
