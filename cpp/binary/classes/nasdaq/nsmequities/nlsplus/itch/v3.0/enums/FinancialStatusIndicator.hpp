#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// For Nasdaq listed issues, denotes when an issue is flagged as deficient, delinquent,
// bankrupt or in a compliance period
enum class FinancialStatusIndicator : char {
    Deficient = 'D',                       // Deficient
    Delinquent = 'E',                      // Delinquent
    Bankrupt = 'Q',                        // Bankrupt
    Suspended = 'S',                       // Suspended
    DeficientAndBankrupt = 'G',            // Deficient And Bankrupt
    DeficientAndDelinquent = 'H',          // Deficient And Delinquent
    DelinquentAndBankrupt = 'J',           // Delinquent And Bankrupt
    DeficientDelinquentAndBankrupt = 'K',  // Deficient Delinquent And Bankrupt
    CreationsOrRedemptionsSuspended = 'C', // Creations Or Redemptions Suspended
    Normal = 'N',                          // Normal
    NotAvailable = ' ',                    // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(FinancialStatusIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, FinancialStatusIndicator value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
