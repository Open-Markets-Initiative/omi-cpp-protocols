#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::psxequities::totalview::itch::v5_0 {

// Indicates if the NASDAQ security is set up for IPO release. This field is intended to help
// NASDAQ market participant firms comply with FINRA Rule 5131(b).
enum class IpoFlag : char {
    Yes = 'Y', // Yes
    No = 'N',  // No
    Na = ' ',  // Na
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IpoFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IpoFlag value);

} // namespace nasdaq::psxequities::totalview::itch::v5_0
