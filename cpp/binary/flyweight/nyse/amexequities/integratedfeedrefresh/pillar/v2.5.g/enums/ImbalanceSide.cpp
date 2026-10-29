#include "ImbalanceSide.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

std::string_view to_string(ImbalanceSide value) {
    switch (value) {
        case ImbalanceSide::BuySide: return "Buy Side";
        case ImbalanceSide::SellSide: return "Sell Side";
        case ImbalanceSide::NoImbalance: return "No Imbalance";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g
