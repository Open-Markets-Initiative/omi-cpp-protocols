#include "SecurityStatusIndicator.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::string_view to_string(SecurityStatusIndicator value) {
    switch (value) {
        case SecurityStatusIndicator::NotApplicable: return "Not Applicable";
        case SecurityStatusIndicator::NewsDissemination: return "News Dissemination";
        case SecurityStatusIndicator::TradingRangeIndication: return "Trading Range Indication";
        case SecurityStatusIndicator::OrderImbalance: return "Order Imbalance";
        case SecurityStatusIndicator::LuldTradingPause: return "Luld Trading Pause";
        case SecurityStatusIndicator::NewsPending: return "News Pending";
        case SecurityStatusIndicator::Resume: return "Resume";
        case SecurityStatusIndicator::Operational: return "Operational";
        case SecurityStatusIndicator::SupPennyTrading: return "Sup Penny Trading";
        case SecurityStatusIndicator::NoOpenNoResume: return "No Open No Resume";
        case SecurityStatusIndicator::LuldPriceBand: return "Luld Price Band";
        case SecurityStatusIndicator::MarketWideCircuitBreakerLevel1Breached: return "Market Wide Circuit Breaker Level 1 Breached";
        case SecurityStatusIndicator::MarketWideCircuitBreakerLevel2Breached: return "Market Wide Circuit Breaker Level 2 Breached";
        case SecurityStatusIndicator::MarketWideCircuitBreakerLevel3Breached: return "Market Wide Circuit Breaker Level 3 Breached";
        case SecurityStatusIndicator::RepublishedLuldPriceBand: return "Republished Luld Price Band";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityStatusIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v1_91
