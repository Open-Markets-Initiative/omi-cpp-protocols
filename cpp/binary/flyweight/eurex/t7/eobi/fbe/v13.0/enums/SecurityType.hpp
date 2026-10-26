#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class SecurityType : std::uint8_t {
    Opt = 1,  // Opt
    Fut = 2,  // Fut
    Mleg = 3, // Mleg
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityType value);

} // namespace eurex::t7::eobi::fbe::v13_0
