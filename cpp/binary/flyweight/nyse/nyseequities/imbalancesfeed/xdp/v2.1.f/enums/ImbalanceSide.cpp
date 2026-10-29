#include "ImbalanceSide.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

std::string_view to_string(ImbalanceSide value) {
    switch (value) {
        case ImbalanceSide::NoImbalance: return "No Imbalance";
        case ImbalanceSide::BuySide: return "Buy Side";
        case ImbalanceSide::SellSide: return "Sell Side";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, ImbalanceSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f
