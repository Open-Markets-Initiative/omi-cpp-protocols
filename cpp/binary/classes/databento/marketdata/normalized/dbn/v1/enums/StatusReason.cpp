#include "StatusReason.hpp"

namespace databento::marketdata::normalized::dbn::v1 {

std::string_view to_string(StatusReason value) {
    switch (value) {
        case StatusReason::None: return "None";
        case StatusReason::Scheduled: return "Scheduled";
        case StatusReason::SurveillanceIntervention: return "Surveillance Intervention";
        case StatusReason::MarketEvent: return "Market Event";
        case StatusReason::InstrumentActivation: return "Instrument Activation";
        case StatusReason::InstrumentExpiration: return "Instrument Expiration";
        case StatusReason::RecoveryInProcess: return "Recovery In Process";
        case StatusReason::Regulatory: return "Regulatory";
        case StatusReason::Administrative: return "Administrative";
        case StatusReason::NonCompliance: return "Non Compliance";
        case StatusReason::FilingsNotCurrent: return "Filings Not Current";
        case StatusReason::SecTradingSuspension: return "Sec Trading Suspension";
        case StatusReason::NewIssue: return "New Issue";
        case StatusReason::IssueAvailable: return "Issue Available";
        case StatusReason::IssuesReviewed: return "Issues Reviewed";
        case StatusReason::FilingReqsSatisfied: return "Filing Reqs Satisfied";
        case StatusReason::NewsPending: return "News Pending";
        case StatusReason::NewsReleased: return "News Released";
        case StatusReason::NewsAndResumptionTimes: return "News And Resumption Times";
        case StatusReason::NewsNotForthcoming: return "News Not Forthcoming";
        case StatusReason::OrderImbalance: return "Order Imbalance";
        case StatusReason::LuldPause: return "Luld Pause";
        case StatusReason::Operational: return "Operational";
        case StatusReason::AdditionalInformationRequested: return "Additional Information Requested";
        case StatusReason::MergerEffective: return "Merger Effective";
        case StatusReason::Etf: return "Etf";
        case StatusReason::CorporateAction: return "Corporate Action";
        case StatusReason::NewSecurityOffering: return "New Security Offering";
        case StatusReason::MarketWideHaltLevel1: return "Market Wide Halt Level1";
        case StatusReason::MarketWideHaltLevel2: return "Market Wide Halt Level2";
        case StatusReason::MarketWideHaltLevel3: return "Market Wide Halt Level3";
        case StatusReason::MarketWideHaltCarryover: return "Market Wide Halt Carryover";
        case StatusReason::MarketWideHaltResumption: return "Market Wide Halt Resumption";
        case StatusReason::QuotationNotAvailable: return "Quotation Not Available";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, StatusReason value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace databento::marketdata::normalized::dbn::v1
