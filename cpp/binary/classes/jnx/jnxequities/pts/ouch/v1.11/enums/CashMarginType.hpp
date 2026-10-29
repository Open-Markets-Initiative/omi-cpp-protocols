#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Cash margin type of order
enum class CashMarginType : char {
    Cash = '1',                    // Cash
    MarginOpenNegotiable = '2',    // Margin Open Negotiable
    MarginCloseNegotiable = '3',   // Margin Close Negotiable
    MarginOpenStandardized = '4',  // Margin Open Standardized
    MarginCloseStandardized = '5', // Margin Close Standardized
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CashMarginType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CashMarginType value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
