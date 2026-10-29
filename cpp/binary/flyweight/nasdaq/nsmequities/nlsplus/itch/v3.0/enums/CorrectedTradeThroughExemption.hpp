#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Used for Sec Regulation Nms Trade Through Exemption codes
enum class CorrectedTradeThroughExemption : char {
    IntermarketSweep = 'F',         // Intermarket Sweep
    OpeningPrint = 'O',             // Opening Print
    DerivativePriced = '4',         // Derivative Priced
    ReOpeningPrint = '5',           // Re Opening Print
    ClosingPrint = '6',             // Closing Print
    QualifiedContingentTrade = '7', // Qualified Contingent Trade
    NotApplicable = ' ',            // Not Applicable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CorrectedTradeThroughExemption value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CorrectedTradeThroughExemption value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
