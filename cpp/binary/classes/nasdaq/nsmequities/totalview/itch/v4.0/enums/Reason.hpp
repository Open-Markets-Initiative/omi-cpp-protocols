#pragma once

#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// Trading Action reason.
// The field is text of more than one byte, so its codes are named constants rather than an enum
struct Reason {
    static constexpr std::string_view HaltNewsPending = "T1";                               // Halt News Pending
    static constexpr std::string_view HaltNewsDisseminated = "T2";                          // Halt News Disseminated
    static constexpr std::string_view SingleSecurityTradingPauseInEffect = "T5";            // Single Security Trading Pause In Effect
    static constexpr std::string_view RegulatoryHaltExtraordinaryMarketActivity = "T6";     // Regulatory Halt Extraordinary Market Activity
    static constexpr std::string_view HaltEtf = "T8";                                       // Halt Etf
    static constexpr std::string_view TradingHaltedForInformationRequested = "T12";         // Trading Halted For Information Requested
    static constexpr std::string_view HaltNonCompliance = "H4";                             // Halt Non Compliance
    static constexpr std::string_view HaltFilingsNotCurrent = "H9";                         // Halt Filings Not Current
    static constexpr std::string_view HaltSecTradingSuspension = "H10";                     // Halt Sec Trading Suspension
    static constexpr std::string_view HaltRegulatoryConcern = "H11";                        // Halt Regulatory Concern
    static constexpr std::string_view OperationsHalt = "O1";                                // Operations Halt
    static constexpr std::string_view IpoIssueNotYetTrading = "IPO1";                       // Ipo Issue Not Yet Trading
    static constexpr std::string_view CorporateAction = "M1";                               // Corporate Action
    static constexpr std::string_view QuotationNotAvailable = "M2";                         // Quotation Not Available
    static constexpr std::string_view NewsAndResumptionTimes = "T3";                        // News And Resumption Times
    static constexpr std::string_view SingleSecurityTradingPauseQuotationOnlyPeriod = "T7"; // Single Security Trading Pause Quotation Only Period
    static constexpr std::string_view QualificationsIssuesReviewed = "R4";                  // Qualifications Issues Reviewed
    static constexpr std::string_view FilingRequirementsSatisfied = "R9";                   // Filing Requirements Satisfied
    static constexpr std::string_view IssuerNewsNotForthcoming = "C3";                      // Issuer News Not Forthcoming
    static constexpr std::string_view QualificationsHaltEnded = "C4";                       // Qualifications Halt Ended
    static constexpr std::string_view QualificationsHaltConcluded = "C9";                   // Qualifications Halt Concluded
    static constexpr std::string_view TradeHaltConcluded = "C11";                           // Trade Halt Concluded
    static constexpr std::string_view NewIssueAvailable = "R1";                             // New Issue Available
    static constexpr std::string_view IssueAvailable = "R2";                                // Issue Available
    static constexpr std::string_view IpoSecurityReleasedForQuotation = "IPOQ";             // Ipo Security Released For Quotation
    static constexpr std::string_view IpoSecurityPositioningWindowExtension = "IPOE";       // Ipo Security Positioning Window Extension
    static constexpr std::string_view ReasonNotAvailable = "    ";                          // Reason Not Available

    // The documented name of a code, or empty for one the specification does not list
    static constexpr std::string_view describe(std::string_view code) {
        if (code == HaltNewsPending) { return "Halt News Pending"; }
        if (code == HaltNewsDisseminated) { return "Halt News Disseminated"; }
        if (code == SingleSecurityTradingPauseInEffect) { return "Single Security Trading Pause In Effect"; }
        if (code == RegulatoryHaltExtraordinaryMarketActivity) { return "Regulatory Halt Extraordinary Market Activity"; }
        if (code == HaltEtf) { return "Halt Etf"; }
        if (code == TradingHaltedForInformationRequested) { return "Trading Halted For Information Requested"; }
        if (code == HaltNonCompliance) { return "Halt Non Compliance"; }
        if (code == HaltFilingsNotCurrent) { return "Halt Filings Not Current"; }
        if (code == HaltSecTradingSuspension) { return "Halt Sec Trading Suspension"; }
        if (code == HaltRegulatoryConcern) { return "Halt Regulatory Concern"; }
        if (code == OperationsHalt) { return "Operations Halt"; }
        if (code == IpoIssueNotYetTrading) { return "Ipo Issue Not Yet Trading"; }
        if (code == CorporateAction) { return "Corporate Action"; }
        if (code == QuotationNotAvailable) { return "Quotation Not Available"; }
        if (code == NewsAndResumptionTimes) { return "News And Resumption Times"; }
        if (code == SingleSecurityTradingPauseQuotationOnlyPeriod) { return "Single Security Trading Pause Quotation Only Period"; }
        if (code == QualificationsIssuesReviewed) { return "Qualifications Issues Reviewed"; }
        if (code == FilingRequirementsSatisfied) { return "Filing Requirements Satisfied"; }
        if (code == IssuerNewsNotForthcoming) { return "Issuer News Not Forthcoming"; }
        if (code == QualificationsHaltEnded) { return "Qualifications Halt Ended"; }
        if (code == QualificationsHaltConcluded) { return "Qualifications Halt Concluded"; }
        if (code == TradeHaltConcluded) { return "Trade Halt Concluded"; }
        if (code == NewIssueAvailable) { return "New Issue Available"; }
        if (code == IssueAvailable) { return "Issue Available"; }
        if (code == IpoSecurityReleasedForQuotation) { return "Ipo Security Released For Quotation"; }
        if (code == IpoSecurityPositioningWindowExtension) { return "Ipo Security Positioning Window Extension"; }
        if (code == ReasonNotAvailable) { return "Reason Not Available"; }
        return {};
    }
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
