#include "MarketStatusMessageType.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(MarketStatusMessageType value) {
    switch (value) {
        case MarketStatusMessageType::MarketWideCircuitBreakerDeclineLevelStatusMessage: return "Market Wide Circuit Breaker Decline Level Status Message";
        case MarketStatusMessageType::MarketWideCircuitBreakerStatusMessage: return "Market Wide Circuit Breaker Status Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MarketStatusMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
