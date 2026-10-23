#include "EventType.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

std::string_view to_string(EventType value) {
    switch (value) {
        case EventType::Activation: return "Activation";
        case EventType::LastEligibleTradeDate: return "Last Eligible Trade Date";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, EventType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_9
