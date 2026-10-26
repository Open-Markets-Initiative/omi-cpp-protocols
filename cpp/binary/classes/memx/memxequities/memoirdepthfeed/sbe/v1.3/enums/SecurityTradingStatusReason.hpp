#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// SecurityTradingStatusReason
enum class SecurityTradingStatusReason : char {
    None = 'X',           // None
    Regulatory = 'R',     // Regulatory
    Administrative = 'A', // Administrative
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityTradingStatusReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityTradingStatusReason value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
