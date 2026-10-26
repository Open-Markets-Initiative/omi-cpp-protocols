#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

// Denotes which System Event is used to determine when trading ceases in this symbol.
enum class OptionClosingType : char {
    Normal = 'N',          // Normal
    Late = 'L',            // Late
    WcoEarlyClosing = 'W', // Wco Early Closing
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OptionClosingType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OptionClosingType value);

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
