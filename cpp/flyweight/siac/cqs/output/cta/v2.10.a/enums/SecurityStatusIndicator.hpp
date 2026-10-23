#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Reports trading suspensions, price indications, trading range indications, LULD Price Bands
// and Market Wide Circuit Breaker activity
enum class SecurityStatusIndicator : char {
    SecurityStatusIndicatorNotApplicable = ' ',   // Security Status Indicator Not Applicable
    AdditionalInformationRequested = 'A',         // Additional Information Requested
    RegulatoryConcern = 'C',                      // Regulatory Concern
    NewsReleased = 'D',                           // News Released
    MergerEffective = 'E',                        // Merger Effective
    EtfComponentPricesNotAvailable = 'F',         // Etf Component Prices Not Available
    TradingRangeIndication = 'G',                 // Trading Range Indication
    OrderImbalance = 'I',                         // Order Imbalance
    LimitUpLimitDownTradingPause = 'M',           // Limit Up Limit Down Trading Pause
    CorporateAction = 'N',                        // Corporate Action
    NewSecurityOffering = 'O',                    // New Security Offering
    NewsPending = 'P',                            // News Pending
    IntradayIndicativeValueNotAvailable = 'V',    // Intraday Indicative Value Not Available
    Resume = 'T',                                 // Resume
    Operational = 'X',                            // Operational
    SupPennyTrading = 'Y',                        // Sup Penny Trading
    Reserved = 'Z',                               // Reserved
    LimitUpLimitDownPriceBand = '0',              // Limit Up Limit Down Price Band
    MarketWideCircuitBreakerLevel1Breached = '1', // Market Wide Circuit Breaker Level 1 Breached
    MarketWideCircuitBreakerLevel2Breached = '2', // Market Wide Circuit Breaker Level 2 Breached
    MarketWideCircuitBreakerLevel3Breached = '3', // Market Wide Circuit Breaker Level 3 Breached
    RepublishedLimitUpLimitDownPriceBand = '9',   // Republished Limit Up Limit Down Price Band
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityStatusIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityStatusIndicator value);

} // namespace siac::cqs::output::cta::v2_10_a
