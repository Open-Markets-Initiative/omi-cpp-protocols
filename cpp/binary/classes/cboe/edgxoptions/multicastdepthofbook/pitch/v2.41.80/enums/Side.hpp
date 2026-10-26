#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// B or S.
enum class Side : char {
    Buy = 'B',  // Buy
    Sell = 'S', // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(Side value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, Side value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
