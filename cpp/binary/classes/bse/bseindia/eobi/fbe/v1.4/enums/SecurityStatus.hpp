#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Instrument status.
enum class SecurityStatus : std::uint8_t {
    Active = 1,    // Active
    Inactive = 2,  // Inactive
    Expired = 4,   // Expired
    Suspended = 9, // Suspended
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatus value);

} // namespace bse::bseindia::eobi::fbe::v1_4
