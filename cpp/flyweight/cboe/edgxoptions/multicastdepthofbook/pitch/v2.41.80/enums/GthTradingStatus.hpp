#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

// C1 Only. H = Halted, Q = Quote-Only, R = Opening Rotation, T = Trading.
enum class GthTradingStatus : char {
    Halted = 'H',          // Halted
    QuoteOnly = 'Q',       // Quote Only
    OpeningRotation = 'R', // Opening Rotation
    Trading = 'T',         // Trading
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(GthTradingStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, GthTradingStatus value);

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
