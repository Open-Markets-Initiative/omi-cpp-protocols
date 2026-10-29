#include "HaltReason.hpp"

namespace siac::cts::output::cta::v2_10 {

std::string_view to_string(HaltReason value) {
    switch (value) {
        case HaltReason::NotApplicable: return "Not Applicable";
        case HaltReason::AdditionalInformationRequested: return "Additional Information Requested";
        case HaltReason::RegulatoryConcern: return "Regulatory Concern";
        case HaltReason::NewsReleased: return "News Released";
        case HaltReason::MergerEffective: return "Merger Effective";
        case HaltReason::EtfComponentPricesNotAvailable: return "Etf Component Prices Not Available";
        case HaltReason::OrderImbalance: return "Order Imbalance";
        case HaltReason::LimitUpLimitDownTradingPause: return "Limit Up Limit Down Trading Pause";
        case HaltReason::CorporateAction: return "Corporate Action";
        case HaltReason::NewSecurityOffering: return "New Security Offering";
        case HaltReason::NewsPending: return "News Pending";
        case HaltReason::IntradayIndicativeValueNotAvailable: return "Intraday Indicative Value Not Available";
        case HaltReason::Operational: return "Operational";
        case HaltReason::SubpennyTrading: return "Subpenny Trading";
        case HaltReason::MarketWideCircuitBreakerLevel1Breached: return "Market Wide Circuit Breaker Level 1 Breached";
        case HaltReason::MarketWideCircuitBreakerLevel2Breached: return "Market Wide Circuit Breaker Level 2 Breached";
        case HaltReason::MarketWideCircuitBreakerLevel3Breached: return "Market Wide Circuit Breaker Level 3 Breached";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, HaltReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_10
