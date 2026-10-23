#include "ImbalanceSide.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(ImbalanceSide value) {
    switch (value) {
        case ImbalanceSide::BuySide: return "Buy Side";
        case ImbalanceSide::SellSide: return "Sell Side";
        case ImbalanceSide::SpaceOr0X20IndicatesNoImbalance: return "Space Or 0 X 20 Indicates No Imbalance";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
