#include "StrategyType.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

std::string_view to_string(StrategyType value) {
    switch (value) {
        case StrategyType::VerticalSpread: return "Vertical Spread";
        case StrategyType::TimeSpread: return "Time Spread";
        case StrategyType::DiagonalSpread: return "Diagonal Spread";
        case StrategyType::Straddle: return "Straddle";
        case StrategyType::Strangle: return "Strangle";
        case StrategyType::Combo: return "Combo";
        case StrategyType::RiskReversal: return "Risk Reversal";
        case StrategyType::RatioSpread: return "Ratio Spread";
        case StrategyType::Custom: return "Custom";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StrategyType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
