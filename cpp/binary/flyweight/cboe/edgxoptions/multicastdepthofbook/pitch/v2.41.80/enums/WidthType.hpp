#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// R = Regular, V = Volatility.
enum class WidthType : char {
    Regular = 'R',       // Regular
    Volatility = 'V',    // Volatility
    MaxQuoteWidth = 'Q', // Max Quote Width
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(WidthType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, WidthType value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
