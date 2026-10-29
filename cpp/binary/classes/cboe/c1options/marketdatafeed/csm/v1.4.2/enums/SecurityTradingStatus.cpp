#include "SecurityTradingStatus.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::string_view to_string(SecurityTradingStatus value) {
    switch (value) {
        case SecurityTradingStatus::Halted: return "Halted";
        case SecurityTradingStatus::Open: return "Open";
        case SecurityTradingStatus::Closed: return "Closed";
        case SecurityTradingStatus::PreOpen: return "Pre Open";
        case SecurityTradingStatus::OpeningRotation: return "Opening Rotation";
        case SecurityTradingStatus::FastMarket: return "Fast Market";
        case SecurityTradingStatus::StrategyMarketInOpeningRotation: return "Strategy Market In Opening Rotation";
        case SecurityTradingStatus::StrategyMarketQuotesNonFirm: return "Strategy Market Quotes Non Firm";
        case SecurityTradingStatus::Suspended: return "Suspended";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
