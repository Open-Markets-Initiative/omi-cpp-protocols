#include "TradeCondition.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

std::string_view to_string(TradeCondition value) {
    switch (value) {
        case TradeCondition::NormalTrade: return "Normal Trade";
        case TradeCondition::OpeningTrade: return "Opening Trade";
        case TradeCondition::SpreadTrade: return "Spread Trade";
        case TradeCondition::BlockTrade: return "Block Trade";
        case TradeCondition::EcrpTrade: return "Ecrp Trade";
        case TradeCondition::Derived: return "Derived";
        case TradeCondition::InterMarketSpreadTrade: return "Inter Market Spread Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
