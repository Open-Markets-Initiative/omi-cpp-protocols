#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

// The Nasdaq Texas cross session for which the message is being generated.
enum class CrossType : char {
    NasdaqTexasOpeningCross = 'O',    // Nasdaq Texas Opening Cross
    NasdaqTexasClosingCross = 'C',    // Nasdaq Texas Closing Cross
    CrossForIpoAndHaltedPaused = 'H', // Cross For Ipo And Halted Paused
    NasdaqTexasCrossNetwork = 'I',    // Nasdaq Texas Cross Network
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
