#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace siac::cqs::output::cta::v2_10_a {

// Identifies whether or not a Short Sale Restriction is in effect
enum class ShortSaleRestrictionIndicator : char {
    ShortSaleRestrictionNotInEffect = ' ', // Short Sale Restriction Not In Effect
    ShortSaleRestrictionActivated = 'A',   // Short Sale Restriction Activated
    ShortSaleRestrictionContinued = 'C',   // Short Sale Restriction Continued
    ShortSaleRestrictionDeactivated = 'D', // Short Sale Restriction Deactivated
    ShortSaleRestrictionInEffect = 'E',    // Short Sale Restriction In Effect
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ShortSaleRestrictionIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ShortSaleRestrictionIndicator value);

} // namespace siac::cqs::output::cta::v2_10_a
