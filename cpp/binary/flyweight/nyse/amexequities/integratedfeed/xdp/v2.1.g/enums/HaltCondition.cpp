#include "HaltCondition.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(HaltCondition value) {
    switch (value) {
        case HaltCondition::SecurityNotDelayedhalted: return "Security Not Delayedhalted";
        case HaltCondition::NotDelayedhaltedNyseTapeAOnly: return "Not Delayedhalted Nyse Tape A Only";
        case HaltCondition::NewsDissemination: return "News Dissemination";
        case HaltCondition::OrderImbalance: return "Order Imbalance";
        case HaltCondition::NewsPending: return "News Pending";
        case HaltCondition::LuldPause: return "Luld Pause";
        case HaltCondition::RelatedSecurityNotUsed: return "Related Security Not Used";
        case HaltCondition::EquipmentChangeover: return "Equipment Changeover";
        case HaltCondition::NoOpenNoResume: return "No Open No Resume";
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

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
