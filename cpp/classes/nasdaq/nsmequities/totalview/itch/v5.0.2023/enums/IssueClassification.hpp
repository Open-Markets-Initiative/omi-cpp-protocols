#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Identifies the security class for the issue as assigned by NASDAQ
enum class IssueClassification : char {
    AmericanDepositaryShare = 'A',    // American Depositary Share
    Bond = 'B',                       // Bond
    CommonStock = 'C',                // Common Stock
    DepositoryReceipt = 'F',          // Depository Receipt
    Sec144A = 'I',                    // Sec 144 A
    LimitedPartnership = 'L',         // Limited Partnership
    Notes = 'N',                      // Notes
    OrdinaryShare = 'O',              // Ordinary Share
    PreferredStock = 'P',             // Preferred Stock
    OtherSecurities = 'Q',            // Other Securities
    Right = 'R',                      // Right
    SharesOfBeneficialInterest = 'S', // Shares Of Beneficial Interest
    ConvertibleDebenture = 'T',       // Convertible Debenture
    Unit = 'U',                       // Unit
    UnitsOfBeneficialInterest = 'V',  // Units Of Beneficial Interest
    Warrant = 'W',                    // Warrant
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IssueClassification value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IssueClassification value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
