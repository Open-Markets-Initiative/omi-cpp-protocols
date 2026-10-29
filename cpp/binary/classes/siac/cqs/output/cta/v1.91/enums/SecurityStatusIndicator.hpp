#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// The Security Status Indicator field is used to report trading suspensions in a security,
// price indications, trading range indications, LULD Price Bands and Market Wide Circuit
// Breaker activity
enum class SecurityStatusIndicator : char {
    NotApplicable = ' ',                          // Not Applicable
    NewsDissemination = 'D',                      // News Dissemination
    TradingRangeIndication = 'G',                 // Trading Range Indication
    OrderImbalance = 'I',                         // Order Imbalance
    LuldTradingPause = 'M',                       // Luld Trading Pause
    NewsPending = 'P',                            // News Pending
    Resume = 'T',                                 // Resume
    Operational = 'X',                            // Operational
    SupPennyTrading = 'Y',                        // Sup Penny Trading
    NoOpenNoResume = 'Z',                         // No Open No Resume
    LuldPriceBand = '0',                          // Luld Price Band
    MarketWideCircuitBreakerLevel1Breached = '1', // Market Wide Circuit Breaker Level 1 Breached
    MarketWideCircuitBreakerLevel2Breached = '2', // Market Wide Circuit Breaker Level 2 Breached
    MarketWideCircuitBreakerLevel3Breached = '3', // Market Wide Circuit Breaker Level 3 Breached
    RepublishedLuldPriceBand = '9',               // Republished Luld Price Band
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatusIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatusIndicator value);

} // namespace siac::cqs::output::cta::v1_91
