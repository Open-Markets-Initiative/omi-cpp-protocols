#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// Additional details about the cause of the status change
enum class StatusReason : std::uint16_t {
    None = 0,                            // None
    Scheduled = 1,                       // Scheduled
    SurveillanceIntervention = 2,        // Surveillance Intervention
    MarketEvent = 3,                     // Market Event
    InstrumentActivation = 4,            // Instrument Activation
    InstrumentExpiration = 5,            // Instrument Expiration
    RecoveryInProcess = 6,               // Recovery In Process
    Regulatory = 10,                     // Regulatory
    Administrative = 11,                 // Administrative
    NonCompliance = 12,                  // Non Compliance
    FilingsNotCurrent = 13,              // Filings Not Current
    SecTradingSuspension = 14,           // Sec Trading Suspension
    NewIssue = 15,                       // New Issue
    IssueAvailable = 16,                 // Issue Available
    IssuesReviewed = 17,                 // Issues Reviewed
    FilingReqsSatisfied = 18,            // Filing Reqs Satisfied
    NewsPending = 30,                    // News Pending
    NewsReleased = 31,                   // News Released
    NewsAndResumptionTimes = 32,         // News And Resumption Times
    NewsNotForthcoming = 33,             // News Not Forthcoming
    OrderImbalance = 40,                 // Order Imbalance
    LuldPause = 50,                      // Luld Pause
    Operational = 60,                    // Operational
    AdditionalInformationRequested = 70, // Additional Information Requested
    MergerEffective = 80,                // Merger Effective
    Etf = 90,                            // Etf
    CorporateAction = 100,               // Corporate Action
    NewSecurityOffering = 110,           // New Security Offering
    MarketWideHaltLevel1 = 120,          // Market Wide Halt Level1
    MarketWideHaltLevel2 = 121,          // Market Wide Halt Level2
    MarketWideHaltLevel3 = 122,          // Market Wide Halt Level3
    MarketWideHaltCarryover = 123,       // Market Wide Halt Carryover
    MarketWideHaltResumption = 124,      // Market Wide Halt Resumption
    QuotationNotAvailable = 130,         // Quotation Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(StatusReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, StatusReason value);

} // namespace databento::marketdata::normalized::dbn::v3
