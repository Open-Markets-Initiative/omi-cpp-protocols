#include "CurrentTradingState.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(CurrentTradingState value) {
    switch (value) {
        case CurrentTradingState::Halt: return "Halt";
        case CurrentTradingState::Trading: return "Trading";
        case CurrentTradingState::BuySideTradingSuspended: return "Buy Side Trading Suspended";
        case CurrentTradingState::SellSideTradingSuspended: return "Sell Side Trading Suspended";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, CurrentTradingState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
