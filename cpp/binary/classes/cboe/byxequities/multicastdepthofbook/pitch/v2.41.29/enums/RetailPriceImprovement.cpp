#include "RetailPriceImprovement.hpp"

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

std::string_view to_string(RetailPriceImprovement value) {
    switch (value) {
        case RetailPriceImprovement::BuySideRpi: return "Buy Side Rpi";
        case RetailPriceImprovement::SellSideRpi: return "Sell Side Rpi";
        case RetailPriceImprovement::BuyAndSellRpi: return "Buy And Sell Rpi";
        case RetailPriceImprovement::NoRpi: return "No Rpi";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RetailPriceImprovement value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
