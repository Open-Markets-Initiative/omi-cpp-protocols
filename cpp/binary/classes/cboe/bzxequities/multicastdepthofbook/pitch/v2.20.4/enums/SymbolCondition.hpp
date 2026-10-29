#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

// "N" = Normal
enum class SymbolCondition : char {
    Normal = 'N',      // Normal
    ClosingOnly = 'C', // Closing Only
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SymbolCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SymbolCondition value);

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
