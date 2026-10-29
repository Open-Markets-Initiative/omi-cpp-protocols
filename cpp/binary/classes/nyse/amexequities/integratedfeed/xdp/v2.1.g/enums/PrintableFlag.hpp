#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

// Printable flag values
enum class PrintableFlag : std::uint8_t {
    NotPrinted = 0, // Not Printed
    Printed = 1,    // Printed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(PrintableFlag value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, PrintableFlag value);

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
