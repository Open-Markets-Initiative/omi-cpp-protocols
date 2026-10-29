#include "MarketWideCircuitBreakerLevelIndicator.hpp"

namespace siac::cts::output::cta::v1_91 {

std::string_view to_string(MarketWideCircuitBreakerLevelIndicator value) {
    switch (value) {
        case MarketWideCircuitBreakerLevelIndicator::NotApplicable: return "Not Applicable";
        case MarketWideCircuitBreakerLevelIndicator::Level1Breached: return "Level 1 Breached";
        case MarketWideCircuitBreakerLevelIndicator::Level2Breached: return "Level 2 Breached";
        case MarketWideCircuitBreakerLevelIndicator::Level3Breached: return "Level 3 Breached";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketWideCircuitBreakerLevelIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v1_91
