#include "SubscriptionReqType.hpp"

namespace cme::globex::mdp3::sbe::v1_9 {

std::string_view to_string(SubscriptionReqType value) {
    switch (value) {
        case SubscriptionReqType::Snapshot: return "Snapshot";
        case SubscriptionReqType::SnapshotAndUpdates: return "Snapshot And Updates";
        case SubscriptionReqType::Unsubscribe: return "Unsubscribe";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SubscriptionReqType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cme::globex::mdp3::sbe::v1_9
