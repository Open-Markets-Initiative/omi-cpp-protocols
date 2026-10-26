#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// SecurityTradingStatus
enum class SecurityTradingStatus : char {
    Halted = 'H',  // Halted
    Paused = 'P',  // Paused
    Quoting = 'Q', // Quoting
    Trading = 'T', // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SecurityTradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SecurityTradingStatus value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
