#include "MarketStatusMessageType.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(MarketStatusMessageType value) {
    switch (value) {
        case MarketStatusMessageType::MarketWideCircuitBreakerDeclineLevelStatusMessage: return "Market Wide Circuit Breaker Decline Level Status Message";
        case MarketStatusMessageType::MarketWideCircuitBreakerStatusMessage: return "Market Wide Circuit Breaker Status Message";
        case MarketStatusMessageType::ApproximateAdjustedVolumeMarketCenterMessage: return "Approximate Adjusted Volume Market Center Message";
        case MarketStatusMessageType::ApproximateTradesAndTotalDollarValueMessage: return "Approximate Trades And Total Dollar Value Message";
        case MarketStatusMessageType::CrossingSessionSummaryMessage: return "Crossing Session Summary Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketStatusMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
