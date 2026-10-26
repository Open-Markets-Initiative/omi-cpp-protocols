#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

// Whether the execution should be reflected in statistics
enum class Printable : char {
    NonPrintable = 'N', // Non Printable
    Printable = 'Y',    // Printable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Printable value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Printable value);

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
