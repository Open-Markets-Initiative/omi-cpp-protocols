#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class TesSecurityMassStatus : std::uint8_t {
    Active = 1,    // Active
    Inactive = 2,  // Inactive
    Expired = 4,   // Expired
    Suspended = 9, // Suspended
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TesSecurityMassStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TesSecurityMassStatus value);

} // namespace eurex::t7::eobi::fbe::v13_0
