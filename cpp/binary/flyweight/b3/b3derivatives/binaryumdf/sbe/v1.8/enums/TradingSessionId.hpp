#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v1_8 {

// tradingSessionID
enum class TradingSessionId : std::uint8_t {
    RegularTradingSession = 1,    // Regular Trading Session
    NonRegularTradingSession = 6, // Non Regular Trading Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingSessionId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingSessionId value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v1_8
