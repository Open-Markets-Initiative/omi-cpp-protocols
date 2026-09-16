#pragma once

#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Trading Action reason
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct ReasonCode {
    static constexpr std::string_view HaltNewsPending = "T1";                               // Halt News Pending
    static constexpr std::string_view HaltNewsDisseminated = "T2";                          // Halt News Disseminated
    static constexpr std::string_view SingleSecurityTradingPauseInEffect = "T5";            // Single Security Trading Pause In Effect
    static constexpr std::string_view RegulatoryHaltExtraordinaryMarketActivity = "T6";     // Regulatory Halt Extraordinary Market Activity
    static constexpr std::string_view HaltEtf = "T8";                                       // Halt Etf
    static constexpr std::string_view TradingHalted = "T12";                                // Trading Halted
    static constexpr std::string_view HaltNonCompliance = "H4";                             // Halt Non Compliance
    static constexpr std::string_view HaltFilingsNotCurrent = "H9";                         // Halt Filings Not Current
    static constexpr std::string_view HaltSecTradingSuspension = "H10";                     // Halt Sec Trading Suspension
    static constexpr std::string_view HaltRegulatoryConcern = "H11";                        // Halt Regulatory Concern
    static constexpr std::string_view OperationsHalt = "O1";                                // Operations Halt
    static constexpr std::string_view VolatilityTradingPause = "LUDP";                      // Volatility Trading Pause
    static constexpr std::string_view StraddleConditionTradingPause = "LUDS";               // Straddle Condition Trading Pause
    static constexpr std::string_view CircuitBreakerHaltLevel1 = "MWC1";                    // Circuit Breaker Halt Level 1
    static constexpr std::string_view CircuitBreakerHaltLevel2 = "MWC2";                    // Circuit Breaker Halt Level 2
    static constexpr std::string_view CircuitBreakerHaltLevel3 = "MWC3";                    // Circuit Breaker Halt Level 3
    static constexpr std::string_view CarryOverCircuitBreakerHalt = "MWC0";                 // Carry Over Circuit Breaker Halt
    static constexpr std::string_view IpoIssue = "IPO1";                                    // Ipo Issue
    static constexpr std::string_view CorporateAction = "M1";                               // Corporate Action
    static constexpr std::string_view NotAvailable = "M2";                                  // Not Available
    static constexpr std::string_view NewsAndResumptionTimes = "T3";                        // News And Resumption Times
    static constexpr std::string_view TradingPauseQuotationOnlyPeriod = "T7";               // Trading Pause Quotation Only Period
    static constexpr std::string_view QualificationsIssuesResolved = "R4";                  // Qualifications Issues Resolved
    static constexpr std::string_view FilingRequirementsSatisfied = "R9";                   // Filing Requirements Satisfied
    static constexpr std::string_view IssuerNewsNotForthcoming = "C3";                      // Issuer News Not Forthcoming
    static constexpr std::string_view QualificationsHaltEnded = "C4";                       // Qualifications Halt Ended
    static constexpr std::string_view QualificationsHaltConcluded = "C9";                   // Qualifications Halt Concluded
    static constexpr std::string_view TradeHaltConcludedByOtherRegulatoryAuthority = "C11"; // Trade Halt Concluded By Other Regulatory Authority
    static constexpr std::string_view MarketWideCircuitBreakerResumption = "MWCQ";          // Market Wide Circuit Breaker Resumption
    static constexpr std::string_view NewIssueAvailable = "R1";                             // New Issue Available
    static constexpr std::string_view IssueAvailable = "R2";                                // Issue Available
    static constexpr std::string_view IpoSecurityReleased = "IPOQ";                         // Ipo Security Released
    static constexpr std::string_view IpoSecurityPositioningWindowExtension = "IPOE";       // Ipo Security Positioning Window Extension
    static constexpr std::string_view ReasonNotAvailable = " ";                             // Reason Not Available

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == HaltNewsPending) { return "Halt News Pending"; }
        if (code == HaltNewsDisseminated) { return "Halt News Disseminated"; }
        if (code == SingleSecurityTradingPauseInEffect) { return "Single Security Trading Pause In Effect"; }
        if (code == RegulatoryHaltExtraordinaryMarketActivity) { return "Regulatory Halt Extraordinary Market Activity"; }
        if (code == HaltEtf) { return "Halt Etf"; }
        if (code == TradingHalted) { return "Trading Halted"; }
        if (code == HaltNonCompliance) { return "Halt Non Compliance"; }
        if (code == HaltFilingsNotCurrent) { return "Halt Filings Not Current"; }
        if (code == HaltSecTradingSuspension) { return "Halt Sec Trading Suspension"; }
        if (code == HaltRegulatoryConcern) { return "Halt Regulatory Concern"; }
        if (code == OperationsHalt) { return "Operations Halt"; }
        if (code == VolatilityTradingPause) { return "Volatility Trading Pause"; }
        if (code == StraddleConditionTradingPause) { return "Straddle Condition Trading Pause"; }
        if (code == CircuitBreakerHaltLevel1) { return "Circuit Breaker Halt Level 1"; }
        if (code == CircuitBreakerHaltLevel2) { return "Circuit Breaker Halt Level 2"; }
        if (code == CircuitBreakerHaltLevel3) { return "Circuit Breaker Halt Level 3"; }
        if (code == CarryOverCircuitBreakerHalt) { return "Carry Over Circuit Breaker Halt"; }
        if (code == IpoIssue) { return "Ipo Issue"; }
        if (code == CorporateAction) { return "Corporate Action"; }
        if (code == NotAvailable) { return "Not Available"; }
        if (code == NewsAndResumptionTimes) { return "News And Resumption Times"; }
        if (code == TradingPauseQuotationOnlyPeriod) { return "Trading Pause Quotation Only Period"; }
        if (code == QualificationsIssuesResolved) { return "Qualifications Issues Resolved"; }
        if (code == FilingRequirementsSatisfied) { return "Filing Requirements Satisfied"; }
        if (code == IssuerNewsNotForthcoming) { return "Issuer News Not Forthcoming"; }
        if (code == QualificationsHaltEnded) { return "Qualifications Halt Ended"; }
        if (code == QualificationsHaltConcluded) { return "Qualifications Halt Concluded"; }
        if (code == TradeHaltConcludedByOtherRegulatoryAuthority) { return "Trade Halt Concluded By Other Regulatory Authority"; }
        if (code == MarketWideCircuitBreakerResumption) { return "Market Wide Circuit Breaker Resumption"; }
        if (code == NewIssueAvailable) { return "New Issue Available"; }
        if (code == IssueAvailable) { return "Issue Available"; }
        if (code == IpoSecurityReleased) { return "Ipo Security Released"; }
        if (code == IpoSecurityPositioningWindowExtension) { return "Ipo Security Positioning Window Extension"; }
        if (code == ReasonNotAvailable) { return "Reason Not Available"; }
        return {};
    }
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
