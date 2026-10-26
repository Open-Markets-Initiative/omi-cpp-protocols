#include "BuySellIndicator.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

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

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
