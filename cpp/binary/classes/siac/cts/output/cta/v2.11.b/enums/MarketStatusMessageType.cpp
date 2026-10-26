#include "MarketStatusMessageType.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(MarketStatusMessageType value) {
    switch (value) {
        case MarketStatusMessageType::MarketWideCircuitBreakerDeclineLevelStatus: return "Market Wide Circuit Breaker Decline Level Status";
        case MarketStatusMessageType::MarketWideCircuitBreakerStatus: return "Market Wide Circuit Breaker Status";
        case MarketStatusMessageType::ApproximateAdjustedVolumeMarketCenter: return "Approximate Adjusted Volume Market Center";
        case MarketStatusMessageType::FractionalApproximateAdjustedVolumeMarketCenter: return "Fractional Approximate Adjusted Volume Market Center";
        case MarketStatusMessageType::ApproximateTradesAndTotalDollarValue: return "Approximate Trades And Total Dollar Value";
        case MarketStatusMessageType::CrossingSessionSummary: return "Crossing Session Summary";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketStatusMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
