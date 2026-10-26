#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

// Y=Printable, N=Non-printable
enum class Printable : char {
    NonPrintable = 'N', // Non Printable
    Printable = 'Y',    // Printable
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Printable value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Printable value);

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
