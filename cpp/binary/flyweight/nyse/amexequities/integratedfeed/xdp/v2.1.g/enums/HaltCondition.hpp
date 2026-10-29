#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// Halt condition indicator
enum class HaltCondition : char {
    SecurityNotDelayedhalted = '~',           // Security Not Delayedhalted
    NotDelayedhaltedNyseTapeAOnly = ' ',      // Not Delayedhalted Nyse Tape A Only
    NewsDissemination = 'D',                  // News Dissemination
    OrderImbalance = 'I',                     // Order Imbalance
    NewsPending = 'P',                        // News Pending
    LuldPause = 'M',                          // Luld Pause
    RelatedSecurityNotUsed = 'S',             // Related Security Not Used
    EquipmentChangeover = 'X',                // Equipment Changeover
    NoOpenNoResume = 'Z',                     // No Open No Resume
    MarketWideCircuitBreakerHaltLevel1 = '1', // Market Wide Circuit Breaker Halt Level 1
    MarketWideCircuitBreakerHaltLevel2 = '2', // Market Wide Circuit Breaker Halt Level 2
    MarketWideCircuitBreakerHaltLevel3 = '3', // Market Wide Circuit Breaker Halt Level 3
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(HaltCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, HaltCondition value);

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
