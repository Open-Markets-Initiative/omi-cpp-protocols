#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g {

// 0 = Not Printed to the SIP. 1 = Printed to the SIP.
enum class PrintableFlag : std::uint8_t {
    NotPrintedToTheSip = 0, // Not Printed To The Sip
    PrintedToTheSip = 1,    // Printed To The Sip
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PrintableFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PrintableFlag value);

} // namespace nyse::arcaequities::integratedfeed::pillar::v2_5_g
