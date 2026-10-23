#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Denotes the reason for the Trading Halt
enum class HaltReason : char {
    HaltReasonNotApplicable = ' ',                // Halt Reason Not Applicable
    AdditionalInformationRequested = 'A',         // Additional Information Requested
    RegulatoryConcern = 'C',                      // Regulatory Concern
    NewsReleased = 'D',                           // News Released
    MergerEffective = 'E',                        // Merger Effective
    EtfComponentPricesNotAvailable = 'F',         // Etf Component Prices Not Available
    OrderImbalance = 'I',                         // Order Imbalance
    LimitUpLimitDownLuldTradingPause = 'M',       // Limit Up Limit Down Luld Trading Pause
    CorporateAction = 'N',                        // Corporate Action
    NewSecurityOffering = 'O',                    // New Security Offering
    NewsPending = 'P',                            // News Pending
    IntradayIndicativeValueNotAvailable = 'V',    // Intraday Indicative Value Not Available
    Operational = 'X',                            // Operational
    SubPennyTrading = 'Y',                        // Sub Penny Trading
    MarketWideCircuitBreakerLevel1Breached = '1', // Market Wide Circuit Breaker Level 1 Breached
    MarketWideCircuitBreakerLevel2Breached = '2', // Market Wide Circuit Breaker Level 2 Breached
    MarketWideCircuitBreakerLevel3Breached = '3', // Market Wide Circuit Breaker Level 3 Breached
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(HaltReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, HaltReason value);

} // namespace siac::cts::output::cta::v2_11_b
