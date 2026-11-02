#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v2 {

// The state of quoting in the instrument
enum class IsQuoting : char {
    NotAvailable = '~', // Not Available
    No = 'N',           // No
    Yes = 'Y',          // Yes
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(IsQuoting value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, IsQuoting value);

} // namespace databento::marketdata::normalized::dbn::v2
