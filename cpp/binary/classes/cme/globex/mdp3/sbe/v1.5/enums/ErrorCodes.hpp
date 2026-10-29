#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cme::globex::mdp3::sbe::v1_5 {

// Error code for reject reason
enum class ErrorCodes : std::uint8_t {
    HmacReject = 0,     // Hmac Reject
    InvalidValue = 1,   // Invalid Value
    SlowConnection = 2, // Slow Connection
    Other = 3,          // Other
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ErrorCodes value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ErrorCodes value);

} // namespace cme::globex::mdp3::sbe::v1_5
