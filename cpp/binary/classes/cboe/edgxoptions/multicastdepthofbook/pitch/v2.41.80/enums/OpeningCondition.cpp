#include "OpeningCondition.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

std::string_view to_string(OpeningCondition value) {
    switch (value) {
        case OpeningCondition::WouldOpen: return "Would Open";
        case OpeningCondition::NeedQuoteToOpen: return "Need Quote To Open";
        case OpeningCondition::NeedMoreBuyers: return "Need More Buyers";
        case OpeningCondition::NeedMoreSellers: return "Need More Sellers";
        case OpeningCondition::CrossedCompositeMarket: return "Crossed Composite Market";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, OpeningCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
