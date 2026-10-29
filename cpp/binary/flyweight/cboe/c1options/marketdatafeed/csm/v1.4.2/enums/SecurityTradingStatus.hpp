#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

enum class SecurityTradingStatus : std::uint8_t {
    Halted = 2,                           // Halted
    Open = 17,                            // Open
    Closed = 18,                          // Closed
    PreOpen = 21,                         // Pre Open
    OpeningRotation = 22,                 // Opening Rotation
    FastMarket = 23,                      // Fast Market
    StrategyMarketInOpeningRotation = 24, // Strategy Market In Opening Rotation
    StrategyMarketQuotesNonFirm = 25,     // Strategy Market Quotes Non Firm
    Suspended = 26,                       // Suspended
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityTradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value);

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
