#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates if the execution should be reflected on time and sale displays and volume
// calculations
enum class Printable : char {
    No = 'N',  // No
    Yes = 'Y', // Yes
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Printable value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Printable value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
