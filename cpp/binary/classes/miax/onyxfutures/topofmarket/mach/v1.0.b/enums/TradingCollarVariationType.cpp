#include "TradingCollarVariationType.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(TradingCollarVariationType value) {
    switch (value) {
        case TradingCollarVariationType::ProductDollarCollarValue: return "Product Dollar Collar Value";
        case TradingCollarVariationType::ProductCollarPercentageValue: return "Product Collar Percentage Value";
        case TradingCollarVariationType::StandardCalendarSpread: return "Standard Calendar Spread";
        case TradingCollarVariationType::EquityCalendarSpread: return "Equity Calendar Spread";
        case TradingCollarVariationType::ButterflySpread: return "Butterfly Spread";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, TradingCollarVariationType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
