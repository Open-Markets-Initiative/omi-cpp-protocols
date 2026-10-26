#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// H = Halted, L = Curb Trading (C1 Only), Q = Quote-Only, R = Opening Rotation, T = RTH
// Trading.
enum class TradingStatus : char {
    Halted = 'H',          // Halted
    CurbTrading = 'L',     // Curb Trading
    QuoteOnly = 'Q',       // Quote Only
    OpeningRotation = 'R', // Opening Rotation
    RthTrading = 'T',      // Rth Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStatus value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
