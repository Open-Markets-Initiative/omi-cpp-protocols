#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cts::output::cta::v2_9 {

// Identifies whether or not a Short Sale Restriction is in effect for a security
enum class ShortSaleRestrictionIndicator : char {
    NotInEffect = ' ',         // Not In Effect
    Activated = 'A',           // Activated
    Continued = 'C',           // Continued
    Deactivated = 'D',         // Deactivated
    RestrictionInEffect = 'E', // Restriction In Effect
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ShortSaleRestrictionIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ShortSaleRestrictionIndicator value);

} // namespace siac::cts::output::cta::v2_9
