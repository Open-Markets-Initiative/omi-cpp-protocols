#include "MarketState.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(MarketState value) {
    switch (value) {
        case MarketState::PreOpening: return "Pre Opening";
        case MarketState::EarlyTradingSession: return "Early Trading Session";
        case MarketState::RegularTradingSession: return "Regular Trading Session";
        case MarketState::LateTradingSession: return "Late Trading Session";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketState value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
