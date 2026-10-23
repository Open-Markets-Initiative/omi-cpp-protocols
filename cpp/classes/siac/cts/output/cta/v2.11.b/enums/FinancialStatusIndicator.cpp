#include "FinancialStatusIndicator.hpp"

namespace siac::cts::output::cta::v2_11_b {

std::string_view to_string(FinancialStatusIndicator value) {
    switch (value) {
        case FinancialStatusIndicator::FinancialStatusNotApplicable: return "Financial Status Not Applicable";
        case FinancialStatusIndicator::Bankrupt: return "Bankrupt";
        case FinancialStatusIndicator::BelowContinuingListingStandards: return "Below Continuing Listing Standards";
        case FinancialStatusIndicator::BankruptBelowContinuingListingStandards: return "Bankrupt Below Continuing Listing Standards";
        case FinancialStatusIndicator::LateFiling: return "Late Filing";
        case FinancialStatusIndicator::BankruptLateFiling: return "Bankrupt Late Filing";
        case FinancialStatusIndicator::BelowContinuingListingStandardsLateFiling: return "Below Continuing Listing Standards Late Filing";
        case FinancialStatusIndicator::BankruptBelowContinuingListingStandardsLateFiling: return "Bankrupt Below Continuing Listing Standards Late Filing";
        case FinancialStatusIndicator::CreationsSuspendedForExchangeTradedProducts: return "Creations Suspended For Exchange Traded Products";
        case FinancialStatusIndicator::RedemptionsSuspendedForExchangeTradedProducts: return "Redemptions Suspended For Exchange Traded Products";
        case FinancialStatusIndicator::LiquidationForExchangeTradedProducts: return "Liquidation For Exchange Traded Products";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, FinancialStatusIndicator value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace siac::cts::output::cta::v2_11_b
