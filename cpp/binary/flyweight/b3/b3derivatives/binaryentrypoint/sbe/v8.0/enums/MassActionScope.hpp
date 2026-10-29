#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0 {

// massActionScope
enum class MassActionScope : std::uint8_t {
    AllOrdersForATradingSession = 6, // All Orders For A Trading Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MassActionScope value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MassActionScope value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_0
