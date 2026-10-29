#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::deepfeed::xdp::v1_3_a {

// Type of Security
enum class SecurityType : char {
    Adr = 'A',                         // Adr
    CommonStock = 'C',                 // Common Stock
    Debentures = 'D',                  // Debentures
    Etf = 'E',                         // Etf
    Foreign = 'F',                     // Foreign
    AmericanDepositoryShares = 'H',    // American Depository Shares
    Units = 'I',                       // Units
    MiscliquidTrust = 'M',             // Miscliquid Trust
    OrdinaryShares = 'O',              // Ordinary Shares
    PreferredStock = 'P',              // Preferred Stock
    Rights = 'R',                      // Rights
    SharesOfBeneficiaryInterest = 'S', // Shares Of Beneficiary Interest
    Test = 'T',                        // Test
    Units2 = 'U',                      // Units
    Warrant = 'W',                     // Warrant
    Index = 'X',                       // Index
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityType value);

} // namespace nyse::amexoptions::deepfeed::xdp::v1_3_a
