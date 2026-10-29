#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::nlsplus::itch::v3_0 {

// Indicates the basis of the reference price for net change calculations
enum class ReferenceForNetChange : char {
    FirstTradePrice = 'F',  // First Trade Price
    UnderwriterPrice = 'W', // Underwriter Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ReferenceForNetChange value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ReferenceForNetChange value);

} // namespace nasdaq::nsmequities::nlsplus::itch::v3_0
