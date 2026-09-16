#include "BuySellIndicator.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::string_view to_string(BuySellIndicator value) {
    switch (value) {
        case BuySellIndicator::Buy: return "Buy";
        case BuySellIndicator::Sell: return "Sell";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, BuySellIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
