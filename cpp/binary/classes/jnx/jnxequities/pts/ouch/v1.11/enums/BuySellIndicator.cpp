#include "BuySellIndicator.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(BuySellIndicator value) {
    switch (value) {
        case BuySellIndicator::Buy: return "Buy";
        case BuySellIndicator::Sell: return "Sell";
        case BuySellIndicator::ShortSell: return "Short Sell";
        case BuySellIndicator::ShortSellExempt: return "Short Sell Exempt";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BuySellIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
