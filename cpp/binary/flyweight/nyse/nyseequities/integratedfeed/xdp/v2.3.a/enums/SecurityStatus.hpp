#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

// The new status that this security is transitioning to.
enum class SecurityStatus : char {
    TradingHalt = '4',                       // Trading Halt
    Resume = '5',                            // Resume
    ShortSaleRestrictionActivatedDay1 = 'A', // Short Sale Restriction Activated Day 1
    ShortSaleRestrictionContinuedDay2 = 'C', // Short Sale Restriction Continued Day 2
    ShortSaleRestrictionDeactivated = 'D',   // Short Sale Restriction Deactivated
    Preopening = 'P',                        // Preopening
    EarlySession = 'E',                      // Early Session
    CoreSession = 'O',                       // Core Session
    LateSessionNonNyseOnly = 'L',            // Late Session Non Nyse Only
    Closed = 'X',                            // Closed
    PriceIndication = 'I',                   // Price Indication
    PreOpeningPriceIndication = 'G',         // Pre Opening Price Indication
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatus value);

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
