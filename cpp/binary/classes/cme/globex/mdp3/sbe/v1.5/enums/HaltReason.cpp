#include "HaltReason.hpp"

namespace cme::globex::mdp3::sbe::v1_5 {

std::string_view to_string(HaltReason value) {
    switch (value) {
        case HaltReason::GroupSchedule: return "Group Schedule";
        case HaltReason::SurveillanceIntervention: return "Surveillance Intervention";
        case HaltReason::MarketEvent: return "Market Event";
        case HaltReason::InstrumentActivation: return "Instrument Activation";
        case HaltReason::InstrumentExpiration: return "Instrument Expiration";
        case HaltReason::Unknown: return "Unknown";
        case HaltReason::RecoveryInProcess: return "Recovery In Process";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, HaltReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_5
