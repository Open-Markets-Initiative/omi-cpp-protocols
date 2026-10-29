#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Indicates if the Nasdaq security is set up for Ipo release
enum class IpoFlag : char {
    NewIpo = 'Y',       // New Ipo
    NotNewIpo = 'N',    // Not New Ipo
    NotAvailable = ' ', // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IpoFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IpoFlag value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
