#include "SessionChangeReason.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(SessionChangeReason value) {
    switch (value) {
        case SessionChangeReason::ScheduledTransition: return "Scheduled Transition";
        case SessionChangeReason::ExtendedByMarketOps: return "Extended By Market Ops";
        case SessionChangeReason::ShortenedByMarketOps: return "Shortened By Market Ops";
        case SessionChangeReason::MarketOrderImbalance: return "Market Order Imbalance";
        case SessionChangeReason::PriceOutsideRange: return "Price Outside Range";
        case SessionChangeReason::AespCircuitBreakerTripped: return "Aesp Circuit Breaker Tripped";
        case SessionChangeReason::Unavailable: return "Unavailable";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SessionChangeReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
