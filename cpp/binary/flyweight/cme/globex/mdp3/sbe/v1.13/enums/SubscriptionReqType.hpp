#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Subscription Request Type indicates to the type of response expected
enum class SubscriptionReqType : std::uint8_t {
    Snapshot = 0,           // Snapshot
    SnapshotAndUpdates = 1, // Snapshot And Updates
    Unsubscribe = 2,        // Unsubscribe
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SubscriptionReqType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SubscriptionReqType value);

} // namespace cme::globex::mdp3::sbe::v1_13
