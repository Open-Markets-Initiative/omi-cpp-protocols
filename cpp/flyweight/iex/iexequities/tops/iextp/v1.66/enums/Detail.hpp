#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace iex::iexequities::tops::iextp::v1_66 {

// Detail of the Reg. SHO short sale price test restriction status
enum class Detail : char {
    NoPriceTestInPlace = ' ', // No Price Test In Place
    Activated = 'A',          // Activated
    Continued = 'C',          // Continued
    Deactivated = 'D',        // Deactivated
    NotAvailable = 'N',       // Not Available
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Detail value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Detail value);

} // namespace iex::iexequities::tops::iextp::v1_66
