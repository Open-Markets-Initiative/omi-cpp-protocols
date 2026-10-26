#include "MarketStatusMessageType.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(MarketStatusMessageType value) {
    switch (value) {
        case MarketStatusMessageType::MarketWideCircuitBreakerDeclineLevelStatus: return "Market Wide Circuit Breaker Decline Level Status";
        case MarketStatusMessageType::MarketWideCircuitBreakerStatus: return "Market Wide Circuit Breaker Status";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketStatusMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
