#include "FinancialStatusIndicator.hpp"

namespace siac::cts::output::cta::v2_9 {

std::string_view to_string(FinancialStatusIndicator value) {
    switch (value) {
        case FinancialStatusIndicator::NotApplicable: return "Not Applicable";
        case FinancialStatusIndicator::Bankrupt: return "Bankrupt";
        case FinancialStatusIndicator::BelowContinuingListingStandards: return "Below Continuing Listing Standards";
        case FinancialStatusIndicator::BankruptAndBelowContinuingListingStandards: return "Bankrupt And Below Continuing Listing Standards";
        case FinancialStatusIndicator::LateFiling: return "Late Filing";
        case FinancialStatusIndicator::BankruptAndLateFiling: return "Bankrupt And Late Filing";
        case FinancialStatusIndicator::BelowContinuingListingStandardsAndLateFiling: return "Below Continuing Listing Standards And Late Filing";
        case FinancialStatusIndicator::BankruptBelowContinuingListingStandardsAndLateFiling: return "Bankrupt Below Continuing Listing Standards And Late Filing";
        case FinancialStatusIndicator::CreationsSuspended: return "Creations Suspended";
        case FinancialStatusIndicator::RedemptionsSuspended: return "Redemptions Suspended";
        case FinancialStatusIndicator::Liquidation: return "Liquidation";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FinancialStatusIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_9
