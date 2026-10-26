#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

// Type of Security used by Pillar markets.
enum class SecurityType : char {
    AmericanDepositaryReceipts = 'A', // American Depositary Receipts
    CommonStock = 'C',                // Common Stock
    Debentures = 'D',                 // Debentures
    ExchangeTradedFunds = 'E',        // Exchange Traded Funds
    Foreign = 'F',                    // Foreign
    AmericanDepositaryShares = 'H',   // American Depositary Shares
    Units = 'I',                      // Units
    IndexLinkedNotes = 'L',           // Index Linked Notes
    OtherBlank = 'M',                 // Other Blank
    OrdinaryShares = 'O',             // Ordinary Shares
    PreferredStock = 'P',             // Preferred Stock
    Rights = 'R',                     // Rights
    SharesOfBeneficialInterest = 'S', // Shares Of Beneficial Interest
    Test = 'T',                       // Test
    ClosedEndFund = 'U',              // Closed End Fund
    Warrants = 'W',                   // Warrants
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityType value);

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
