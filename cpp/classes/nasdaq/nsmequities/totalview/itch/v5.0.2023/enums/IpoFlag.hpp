#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates if the NASDAQ security is set up for IPO release
enum class IpoFlag : char {
    SetUpForIpoRelease = 'Y',      // Set Up For Ipo Release
    NotSetUpForIpoRelease = 'N',   // Not Set Up For Ipo Release
    NonIpoNewListedSecurity = 'Z', // Non Ipo New Listed Security
    NotAvailable = ' ',            // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IpoFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IpoFlag value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
