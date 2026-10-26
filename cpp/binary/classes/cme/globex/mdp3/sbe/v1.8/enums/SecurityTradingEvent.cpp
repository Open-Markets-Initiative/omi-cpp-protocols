#include "SecurityTradingEvent.hpp"

namespace cme::globex::mdp3::sbe::v1_8 {

std::string_view to_string(SecurityTradingEvent value) {
    switch (value) {
        case SecurityTradingEvent::NoEvent: return "No Event";
        case SecurityTradingEvent::NoCancel: return "No Cancel";
        case SecurityTradingEvent::ResetStatistics: return "Reset Statistics";
        case SecurityTradingEvent::ImpliedMatchingOn: return "Implied Matching On";
        case SecurityTradingEvent::ImpliedMatchingOff: return "Implied Matching Off";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SecurityTradingEvent value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_8
