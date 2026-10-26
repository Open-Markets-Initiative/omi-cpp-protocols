#include "SecurityStatusIndicator.hpp"

namespace siac::cqs::output::cta::v2_10_a {

std::string_view to_string(SecurityStatusIndicator value) {
    switch (value) {
        case SecurityStatusIndicator::SecurityStatusIndicatorNotApplicable: return "Security Status Indicator Not Applicable";
        case SecurityStatusIndicator::AdditionalInformationRequested: return "Additional Information Requested";
        case SecurityStatusIndicator::RegulatoryConcern: return "Regulatory Concern";
        case SecurityStatusIndicator::NewsReleased: return "News Released";
        case SecurityStatusIndicator::MergerEffective: return "Merger Effective";
        case SecurityStatusIndicator::EtfComponentPricesNotAvailable: return "Etf Component Prices Not Available";
        case SecurityStatusIndicator::TradingRangeIndication: return "Trading Range Indication";
        case SecurityStatusIndicator::OrderImbalance: return "Order Imbalance";
        case SecurityStatusIndicator::LimitUpLimitDownTradingPause: return "Limit Up Limit Down Trading Pause";
        case SecurityStatusIndicator::CorporateAction: return "Corporate Action";
        case SecurityStatusIndicator::NewSecurityOffering: return "New Security Offering";
        case SecurityStatusIndicator::NewsPending: return "News Pending";
        case SecurityStatusIndicator::IntradayIndicativeValueNotAvailable: return "Intraday Indicative Value Not Available";
        case SecurityStatusIndicator::Resume: return "Resume";
        case SecurityStatusIndicator::Operational: return "Operational";
        case SecurityStatusIndicator::SupPennyTrading: return "Sup Penny Trading";
        case SecurityStatusIndicator::Reserved: return "Reserved";
        case SecurityStatusIndicator::LimitUpLimitDownPriceBand: return "Limit Up Limit Down Price Band";
        case SecurityStatusIndicator::MarketWideCircuitBreakerLevel1Breached: return "Market Wide Circuit Breaker Level 1 Breached";
        case SecurityStatusIndicator::MarketWideCircuitBreakerLevel2Breached: return "Market Wide Circuit Breaker Level 2 Breached";
        case SecurityStatusIndicator::MarketWideCircuitBreakerLevel3Breached: return "Market Wide Circuit Breaker Level 3 Breached";
        case SecurityStatusIndicator::RepublishedLimitUpLimitDownPriceBand: return "Republished Limit Up Limit Down Price Band";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityStatusIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cqs::output::cta::v2_10_a
