#pragma once

#include <string_view>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// Trading Action reason
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct TradingActionReason {
    static constexpr std::string_view HaltNewsPending = "T1";                                        // Halt News Pending
    static constexpr std::string_view HaltNewsDisseminated = "T2";                                   // Halt News Disseminated
    static constexpr std::string_view SingleSecurityTradingPauseInEffect = "T5";                     // Single Security Trading Pause In Effect
    static constexpr std::string_view RegulatoryHalt = "T6";                                         // Regulatory Halt
    static constexpr std::string_view HaltEtf = "T8";                                                // Halt Etf
    static constexpr std::string_view TradingHalted = "T12";                                         // Trading Halted
    static constexpr std::string_view HaltNonCompliance = "H4";                                      // Halt Non Compliance
    static constexpr std::string_view HaltFilingsNotCurrent = "H9";                                  // Halt Filings Not Current
    static constexpr std::string_view HaltSecTradingSuspension = "H10";                              // Halt Sec Trading Suspension
    static constexpr std::string_view HaltRegulatoryConcern = "H11";                                 // Halt Regulatory Concern
    static constexpr std::string_view OperationsHalt = "O1";                                         // Operations Halt
    static constexpr std::string_view VolatilityTradingPause = "LUDP";                               // Volatility Trading Pause
    static constexpr std::string_view VolatilityTradingPauseStraddleCondition = "LUDS";              // Volatility Trading Pause Straddle Condition
    static constexpr std::string_view MarketWideCircuitBreakerHaltLevel1 = "MWC1";                   // Market Wide Circuit Breaker Halt Level 1
    static constexpr std::string_view MarketWideCircuitBreakerHaltLevel2 = "MWC2";                   // Market Wide Circuit Breaker Halt Level 2
    static constexpr std::string_view MarketWideCircuitBreakerHaltLevel3 = "MWC3";                   // Market Wide Circuit Breaker Halt Level 3
    static constexpr std::string_view MarketWideCircuitBreakerHaltCarryOverFromPreviousDay = "MWC0"; // Market Wide Circuit Breaker Halt Carry Over From Previous Day
    static constexpr std::string_view IpoIssueNotYetTrading = "IPO1";                                // Ipo Issue Not Yet Trading
    static constexpr std::string_view CorporateAction = "M1";                                        // Corporate Action
    static constexpr std::string_view QuotationNotAvailable = "M2";                                  // Quotation Not Available
    static constexpr std::string_view ReasonNotAvailable = " ";                                      // Reason Not Available
    static constexpr std::string_view NewsAndResumptionTimes = "T3";                                 // News And Resumption Times
    static constexpr std::string_view SingleSecurityTradingPauseQuotationOnlyPeriod = "T7";          // Single Security Trading Pause Quotation Only Period
    static constexpr std::string_view QualificationsIssuesReviewedResolved = "R4";                   // Qualifications Issues Reviewed Resolved
    static constexpr std::string_view FilingRequirementsSatisfiedResolved = "R9";                    // Filing Requirements Satisfied Resolved
    static constexpr std::string_view IssuerNewsNotForthcoming = "C3";                               // Issuer News Not Forthcoming
    static constexpr std::string_view QualificationsHaltEnded = "C4";                                // Qualifications Halt Ended
    static constexpr std::string_view QualificationsHaltConcluded = "C9";                            // Qualifications Halt Concluded
    static constexpr std::string_view TradeHaltConcludedByOtherRegulatoryAuth = "C11";               // Trade Halt Concluded By Other Regulatory Auth
    static constexpr std::string_view MarketWideCircuitBreakerResumption = "MWCQ";                   // Market Wide Circuit Breaker Resumption
    static constexpr std::string_view NewIssueAvailable = "R1";                                      // New Issue Available
    static constexpr std::string_view IssueAvailable = "R2";                                         // Issue Available
    static constexpr std::string_view IpoSecurityReleasedForQuotation = "IPOQ";                      // Ipo Security Released For Quotation
    static constexpr std::string_view IpoSecurityPositioningWindowExtension = "IPOE";                // Ipo Security Positioning Window Extension

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == HaltNewsPending) { return "Halt News Pending"; }
        if (code == HaltNewsDisseminated) { return "Halt News Disseminated"; }
        if (code == SingleSecurityTradingPauseInEffect) { return "Single Security Trading Pause In Effect"; }
        if (code == RegulatoryHalt) { return "Regulatory Halt"; }
        if (code == HaltEtf) { return "Halt Etf"; }
        if (code == TradingHalted) { return "Trading Halted"; }
        if (code == HaltNonCompliance) { return "Halt Non Compliance"; }
        if (code == HaltFilingsNotCurrent) { return "Halt Filings Not Current"; }
        if (code == HaltSecTradingSuspension) { return "Halt Sec Trading Suspension"; }
        if (code == HaltRegulatoryConcern) { return "Halt Regulatory Concern"; }
        if (code == OperationsHalt) { return "Operations Halt"; }
        if (code == VolatilityTradingPause) { return "Volatility Trading Pause"; }
        if (code == VolatilityTradingPauseStraddleCondition) { return "Volatility Trading Pause Straddle Condition"; }
        if (code == MarketWideCircuitBreakerHaltLevel1) { return "Market Wide Circuit Breaker Halt Level 1"; }
        if (code == MarketWideCircuitBreakerHaltLevel2) { return "Market Wide Circuit Breaker Halt Level 2"; }
        if (code == MarketWideCircuitBreakerHaltLevel3) { return "Market Wide Circuit Breaker Halt Level 3"; }
        if (code == MarketWideCircuitBreakerHaltCarryOverFromPreviousDay) { return "Market Wide Circuit Breaker Halt Carry Over From Previous Day"; }
        if (code == IpoIssueNotYetTrading) { return "Ipo Issue Not Yet Trading"; }
        if (code == CorporateAction) { return "Corporate Action"; }
        if (code == QuotationNotAvailable) { return "Quotation Not Available"; }
        if (code == ReasonNotAvailable) { return "Reason Not Available"; }
        if (code == NewsAndResumptionTimes) { return "News And Resumption Times"; }
        if (code == SingleSecurityTradingPauseQuotationOnlyPeriod) { return "Single Security Trading Pause Quotation Only Period"; }
        if (code == QualificationsIssuesReviewedResolved) { return "Qualifications Issues Reviewed Resolved"; }
        if (code == FilingRequirementsSatisfiedResolved) { return "Filing Requirements Satisfied Resolved"; }
        if (code == IssuerNewsNotForthcoming) { return "Issuer News Not Forthcoming"; }
        if (code == QualificationsHaltEnded) { return "Qualifications Halt Ended"; }
        if (code == QualificationsHaltConcluded) { return "Qualifications Halt Concluded"; }
        if (code == TradeHaltConcludedByOtherRegulatoryAuth) { return "Trade Halt Concluded By Other Regulatory Auth"; }
        if (code == MarketWideCircuitBreakerResumption) { return "Market Wide Circuit Breaker Resumption"; }
        if (code == NewIssueAvailable) { return "New Issue Available"; }
        if (code == IssueAvailable) { return "Issue Available"; }
        if (code == IpoSecurityReleasedForQuotation) { return "Ipo Security Released For Quotation"; }
        if (code == IpoSecurityPositioningWindowExtension) { return "Ipo Security Positioning Window Extension"; }
        return {};
    }
};

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
