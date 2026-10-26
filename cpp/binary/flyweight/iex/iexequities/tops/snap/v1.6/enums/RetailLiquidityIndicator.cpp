#include "RetailLiquidityIndicator.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

std::string_view to_string(RetailLiquidityIndicator value) {
    switch (value) {
        case RetailLiquidityIndicator::NotApplicable: return "Not Applicable";
        case RetailLiquidityIndicator::BuyInterest: return "Buy Interest";
        case RetailLiquidityIndicator::SellInterest: return "Sell Interest";
        case RetailLiquidityIndicator::BuyAndSellInterest: return "Buy And Sell Interest";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, RetailLiquidityIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::tops::snap::v1_6
