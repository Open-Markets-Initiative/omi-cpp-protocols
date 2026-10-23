#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_11_b {

// Identifies the financial status of the security
enum class FinancialStatusIndicator : char {
    FinancialStatusNotApplicable = '0',                      // Financial Status Not Applicable
    Bankrupt = '1',                                          // Bankrupt
    BelowContinuingListingStandards = '2',                   // Below Continuing Listing Standards
    BankruptBelowContinuingListingStandards = '3',           // Bankrupt Below Continuing Listing Standards
    LateFiling = '4',                                        // Late Filing
    BankruptLateFiling = '5',                                // Bankrupt Late Filing
    BelowContinuingListingStandardsLateFiling = '6',         // Below Continuing Listing Standards Late Filing
    BankruptBelowContinuingListingStandardsLateFiling = '7', // Bankrupt Below Continuing Listing Standards Late Filing
    CreationsSuspendedForExchangeTradedProducts = '8',       // Creations Suspended For Exchange Traded Products
    RedemptionsSuspendedForExchangeTradedProducts = '9',     // Redemptions Suspended For Exchange Traded Products
    LiquidationForExchangeTradedProducts = 'A',              // Liquidation For Exchange Traded Products
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FinancialStatusIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FinancialStatusIndicator value);

} // namespace siac::cts::output::cta::v2_11_b
