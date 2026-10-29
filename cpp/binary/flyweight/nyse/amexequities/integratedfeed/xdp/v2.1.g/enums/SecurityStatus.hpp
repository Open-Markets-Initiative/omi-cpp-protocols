#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// The new status that this security is transitioning to.
enum class SecurityStatus : char {
    OpeningDelay = '3',                      // Opening Delay
    TradingHalt = '4',                       // Trading Halt
    Resume = '5',                            // Resume
    NoOpennoResume = '6',                    // No Openno Resume
    ShortSaleRestrictionActivatedDay1 = 'A', // Short Sale Restriction Activated Day 1
    ShortSaleRestrictionContinuedDay2 = 'C', // Short Sale Restriction Continued Day 2
    ShortSaleRestrictionDeactivated = 'D',   // Short Sale Restriction Deactivated
    PreOpening = 'P',                        // Pre Opening
    EarlySession = 'E',                      // Early Session
    CoreSession = 'O',                       // Core Session
    LateSessionNonNyseOnly = 'L',            // Late Session Non Nyse Only
    Closed = 'X',                            // Closed
    Time = 'T',                              // Time
    PriceIndication = 'I',                   // Price Indication
    PreOpeningPriceIndication = 'G',         // Pre Opening Price Indication
    Rule15Indication = 'R',                  // Rule 15 Indication
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatus value);

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
