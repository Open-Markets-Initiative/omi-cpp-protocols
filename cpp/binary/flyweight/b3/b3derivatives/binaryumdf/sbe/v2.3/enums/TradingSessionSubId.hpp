#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryumdf::sbe::v2_3 {

// tradingSessionSubID
enum class TradingSessionSubId : std::uint8_t {
    Pause = 2,              // Pause
    Close = 4,              // Close
    Open = 17,              // Open
    PreClose = 18,          // Pre Close
    UnknownOrInvalid = 20,  // Unknown Or Invalid
    PreOpen = 21,           // Pre Open
    FinalClosingCall = 101, // Final Closing Call
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingSessionSubId value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingSessionSubId value);

} // namespace b3::b3derivatives::binaryumdf::sbe::v2_3
