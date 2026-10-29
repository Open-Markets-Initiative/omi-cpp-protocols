#include "MarketState.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::string_view to_string(MarketState value) {
    switch (value) {
        case MarketState::PreOpening: return "Pre Opening";
        case MarketState::Extended1TradingSession: return "Extended 1 Trading Session";
        case MarketState::RegularTradingSession: return "Regular Trading Session";
        case MarketState::Extended2TradingSession: return "Extended 2 Trading Session";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
