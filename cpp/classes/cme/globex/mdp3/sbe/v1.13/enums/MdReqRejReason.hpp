#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_13 {

// Market Data Request Reject reason code
enum class MdReqRejReason : std::uint8_t {
    UnknownSecurity = 0,  // Unknown Security
    UnknownMessage = 1,   // Unknown Message
    UnsupportedScope = 2, // Unsupported Scope
    Other = 3,            // Other
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MdReqRejReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MdReqRejReason value);

} // namespace cme::globex::mdp3::sbe::v1_13
