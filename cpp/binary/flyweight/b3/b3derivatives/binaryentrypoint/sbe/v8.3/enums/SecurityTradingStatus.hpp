#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// securityTradingStatus
enum class SecurityTradingStatus : std::uint8_t {
    TradingHalt = 2,        // Trading Halt
    NoOpen = 4,             // No Open
    ReadyToTrade = 17,      // Ready To Trade
    Forbidden = 18,         // Forbidden
    UnknownOrInvalid = 20,  // Unknown Or Invalid
    PreOpen = 21,           // Pre Open
    FinalClosingCall = 101, // Final Closing Call
    Reserved = 110,         // Reserved
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityTradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
