#include "BuySellIndicator.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::string_view to_string(BuySellIndicator value) {
    switch (value) {
        case BuySellIndicator::BuyOrder: return "Buy Order";
        case BuySellIndicator::SellOrder: return "Sell Order";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BuySellIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
