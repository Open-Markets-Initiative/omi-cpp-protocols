#include "SessionChangeReason.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(SessionChangeReason value) {
    switch (value) {
        case SessionChangeReason::ScheduledTransition: return "Scheduled Transition";
        case SessionChangeReason::ExtendedByMarketOps: return "Extended By Market Ops";
        case SessionChangeReason::ShortenedByMarketOps: return "Shortened By Market Ops";
        case SessionChangeReason::MarketOrderImbalance: return "Market Order Imbalance";
        case SessionChangeReason::PriceOutsideRange: return "Price Outside Range";
        case SessionChangeReason::UnavailableRecoveryServiceOnly: return "Unavailable Recovery Service Only";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SessionChangeReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::millennium::level2::mitch::v11_9
