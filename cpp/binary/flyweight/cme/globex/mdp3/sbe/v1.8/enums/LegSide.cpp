#include "LegSide.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

std::string_view to_string(LegSide value) {
    switch (value) {
        case LegSide::BuySide: return "Buy Side";
        case LegSide::SellSide: return "Sell Side";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, LegSide value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_8
