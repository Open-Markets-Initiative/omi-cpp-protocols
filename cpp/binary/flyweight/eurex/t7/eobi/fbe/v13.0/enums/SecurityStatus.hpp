#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class SecurityStatus : std::uint8_t {
    Active = 1,                  // Active
    Inactive = 2,                // Inactive
    Expired = 4,                 // Expired
    KnockedOut = 6,              // Knocked Out
    KnockOutRevoked = 7,         // Knock Out Revoked
    Suspended = 9,               // Suspended
    PendingDeletion = 11,        // Pending Deletion
    KnockedOutAndSuspended = 12, // Knocked Out And Suspended
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatus value);

} // namespace eurex::t7::eobi::fbe::v13_0
