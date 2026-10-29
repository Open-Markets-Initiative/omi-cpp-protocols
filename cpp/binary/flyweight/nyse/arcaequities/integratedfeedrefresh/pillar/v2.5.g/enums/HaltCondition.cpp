#include "HaltCondition.hpp"

namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g {

std::string_view to_string(HaltCondition value) {
    switch (value) {
        case HaltCondition::SecurityNotDelayedhalted: return "Security Not Delayedhalted";
        case HaltCondition::NewsReleasedNewsDissemination: return "News Released News Dissemination";
        case HaltCondition::OrderImbalance: return "Order Imbalance";
        case HaltCondition::NewsPending: return "News Pending";
        case HaltCondition::LuldPause: return "Luld Pause";
        case HaltCondition::EquipmentChangeover: return "Equipment Changeover";
        case HaltCondition::AdditionalInformationRequested: return "Additional Information Requested";
        case HaltCondition::RegulatoryConcern: return "Regulatory Concern";
        case HaltCondition::MergerEffective: return "Merger Effective";
        case HaltCondition::EtfComponentPricesNotAvailable: return "Etf Component Prices Not Available";
        case HaltCondition::CorporateAction: return "Corporate Action";
        case HaltCondition::NewSecurityOffering: return "New Security Offering";
        case HaltCondition::IntradayIndicativeValueNotAvailable: return "Intraday Indicative Value Not Available";
        case HaltCondition::Suspend: return "Suspend";
        case HaltCondition::MarketWideCircuitBreakerHaltLevel1: return "Market Wide Circuit Breaker Halt Level 1";
        case HaltCondition::MarketWideCircuitBreakerHaltLevel2: return "Market Wide Circuit Breaker Halt Level 2";
        case HaltCondition::MarketWideCircuitBreakerHaltLevel3: return "Market Wide Circuit Breaker Halt Level 3";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, HaltCondition value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nyse::arcaequities::integratedfeedrefresh::pillar::v2_5_g
