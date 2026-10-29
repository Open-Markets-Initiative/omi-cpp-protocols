#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

// The halt or other condition associated with the security status change.
enum class HaltCondition : char {
    SecurityNotDelayedhalted = '~',            // Security Not Delayedhalted
    NewsReleasedNewsDissemination = 'D',       // News Released News Dissemination
    OrderImbalance = 'I',                      // Order Imbalance
    NewsPending = 'P',                         // News Pending
    LuldPause = 'M',                           // Luld Pause
    EquipmentChangeover = 'X',                 // Equipment Changeover
    AdditionalInformationRequested = 'A',      // Additional Information Requested
    RegulatoryConcern = 'C',                   // Regulatory Concern
    MergerEffective = 'E',                     // Merger Effective
    EtfComponentPricesNotAvailable = 'F',      // Etf Component Prices Not Available
    CorporateAction = 'N',                     // Corporate Action
    NewSecurityOffering = 'O',                 // New Security Offering
    IntradayIndicativeValueNotAvailable = 'V', // Intraday Indicative Value Not Available
    Suspend = '6',                             // Suspend
    MarketWideCircuitBreakerHaltLevel1 = '1',  // Market Wide Circuit Breaker Halt Level 1
    MarketWideCircuitBreakerHaltLevel2 = '2',  // Market Wide Circuit Breaker Halt Level 2
    MarketWideCircuitBreakerHaltLevel3 = '3',  // Market Wide Circuit Breaker Halt Level 3
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(HaltCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, HaltCondition value);

} // namespace nyse::nationalequities::bbo::pillar::v2_5_d
