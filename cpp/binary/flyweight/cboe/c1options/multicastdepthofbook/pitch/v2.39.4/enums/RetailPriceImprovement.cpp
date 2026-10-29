#include "RetailPriceImprovement.hpp"

namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4 {

std::string_view to_string(RetailPriceImprovement value) {
    switch (value) {
        case RetailPriceImprovement::BuySide: return "Buy Side";
        case RetailPriceImprovement::SellSide: return "Sell Side";
        case RetailPriceImprovement::BuyAndSell: return "Buy And Sell";
        case RetailPriceImprovement::NoRpi: return "No Rpi";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RetailPriceImprovement value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::c1options::multicastdepthofbook::pitch::v2_39_4
