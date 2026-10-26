#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

// TradingSession
enum class TradingSession : char {
    Opening = '1',     // Opening
    Trading = '2',     // Trading
    PostTrading = '3', // Post Trading
    Closed = '4',      // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingSession value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingSession value);

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
