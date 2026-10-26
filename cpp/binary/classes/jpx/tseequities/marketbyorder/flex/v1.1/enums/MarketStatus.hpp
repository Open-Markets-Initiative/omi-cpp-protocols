#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

// Indicates market status
enum class MarketStatus : std::uint8_t {
    MorningSessionOrderAcceptanceTime = 11,   // Morning Session Order Acceptance Time
    MorningSessionTradingHours = 12,          // Morning Session Trading Hours
    EndOfMorningSession = 19,                 // End Of Morning Session
    AfternoonSessionOrderAcceptanceTime = 21, // Afternoon Session Order Acceptance Time
    AfternoonSessionTradingHours = 22,        // Afternoon Session Trading Hours
    AfternoonSessionPreclosing = 23,          // Afternoon Session Preclosing
    EndOfAfternoonSession = 29,               // End Of Afternoon Session
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketStatus value);

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
