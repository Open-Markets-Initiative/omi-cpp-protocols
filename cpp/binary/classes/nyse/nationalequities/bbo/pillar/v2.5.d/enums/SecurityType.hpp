#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::nationalequities::bbo::pillar::v2_5_d {

// Type of Security used by Pillar-powered markets.
enum class SecurityType : char {
    Adr = 'A',                         // Adr
    CommonStock = 'C',                 // Common Stock
    Debentures = 'D',                  // Debentures
    Etf = 'E',                         // Etf
    Foreign = 'F',                     // Foreign
    UsDepositaryShares = 'H',          // Us Depositary Shares
    Units = 'I',                       // Units
    IndexLinkedNotes = 'L',            // Index Linked Notes
    MiscliquidTrust = 'M',             // Miscliquid Trust
    OrdinaryShares = 'O',              // Ordinary Shares
    PreferredStock = 'P',              // Preferred Stock
    Rights = 'R',                      // Rights
    SharesOfBeneficiaryInterest = 'S', // Shares Of Beneficiary Interest
    Test = 'T',                        // Test
    ClosedEndFund = 'U',               // Closed End Fund
    Warrant = 'W',                     // Warrant
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityType value);

} // namespace nyse::nationalequities::bbo::pillar::v2_5_d
