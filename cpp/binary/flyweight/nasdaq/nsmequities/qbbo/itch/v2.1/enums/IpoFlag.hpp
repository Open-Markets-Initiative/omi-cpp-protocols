#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

// Indicates if the Nasdaq security is set up for IPO release.
enum class IpoFlag : char {
    IpoSecurity = 'Y',             // Ipo Security
    NotIpoSecurity = 'N',          // Not Ipo Security
    NonIpoNewListedSecurity = 'Z', // Non Ipo New Listed Security
    NotAvailable = ' ',            // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IpoFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IpoFlag value);

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
