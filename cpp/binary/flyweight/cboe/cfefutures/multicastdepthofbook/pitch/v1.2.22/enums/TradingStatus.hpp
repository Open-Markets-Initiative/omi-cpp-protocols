#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

// Trading Status Values
enum class TradingStatus : char {
    Suspended = 'S', // Suspended
    Queuing = 'Q',   // Queuing
    Trading = 'T',   // Trading
    Halted = 'H',    // Halted
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStatus value);

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
