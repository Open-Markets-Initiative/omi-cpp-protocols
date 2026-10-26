#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2017 {

// The NASDAQ cross session for which the message is being generated.
enum class CrossType : char {
    OpeningCross = 'O',                   // Opening Cross
    ClosingCross = 'C',                   // Closing Cross
    CrossHaltedOrPaused = 'H',            // Cross Halted Or Paused
    IntradayCrossAndPostCloseCross = 'I', // Intraday Cross And Post Close Cross
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2017
