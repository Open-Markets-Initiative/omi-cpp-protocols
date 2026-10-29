#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// tradingSessionID
enum class TradingSessionId : std::uint8_t {
    RegularDaySession = 1, // Regular Day Session
    NonRegularSession = 6, // Non Regular Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingSessionId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingSessionId value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
