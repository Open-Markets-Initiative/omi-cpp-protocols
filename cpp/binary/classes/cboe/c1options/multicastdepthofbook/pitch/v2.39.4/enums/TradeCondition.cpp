#include "TradeCondition.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

std::string_view to_string(TradeCondition value) {
    switch (value) {
        case TradeCondition::NormalTrade: return "Normal Trade";
        case TradeCondition::SpreadTrade: return "Spread Trade";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradeCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
