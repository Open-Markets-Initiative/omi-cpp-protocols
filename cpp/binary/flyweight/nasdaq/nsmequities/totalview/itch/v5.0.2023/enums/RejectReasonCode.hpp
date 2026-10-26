#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Login Reject Codes
enum class RejectReasonCode : char {
    NotAuthorized = 'A',       // Not Authorized
    SessionNotAvailable = 'S', // Session Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RejectReasonCode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RejectReasonCode value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
