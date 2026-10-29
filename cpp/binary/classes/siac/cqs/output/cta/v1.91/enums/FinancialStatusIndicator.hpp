#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v1_91 {

// Identifies the financial status of the security.
enum class FinancialStatusIndicator : char {
    FinancialStatusNotApplicable = '0',                         // Financial Status Not Applicable
    Bankrupt = '1',                                             // Bankrupt
    BelowContinuingListingStandards = '2',                      // Below Continuing Listing Standards
    BankruptAndBelowContinuingListingStandards = '3',           // Bankrupt And Below Continuing Listing Standards
    LateFiling = '4',                                           // Late Filing
    BankruptAndLateFiling = '5',                                // Bankrupt And Late Filing
    BelowContinuingListingStandardsAndLateFiling = '6',         // Below Continuing Listing Standards And Late Filing
    BankruptBelowContinuingListingStandardsAndLateFiling = '7', // Bankrupt Below Continuing Listing Standards And Late Filing
    CreationsSuspended = '8',                                   // Creations Suspended
    RedemptionsSuspended = '9',                                 // Redemptions Suspended
    Liquidation = 'A',                                          // Liquidation
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FinancialStatusIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FinancialStatusIndicator value);

} // namespace siac::cqs::output::cta::v1_91
