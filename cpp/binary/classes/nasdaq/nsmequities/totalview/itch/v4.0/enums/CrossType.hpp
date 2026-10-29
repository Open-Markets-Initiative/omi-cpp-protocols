#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

// The NASDAQ cross session for which the message is being generated.
enum class CrossType : char {
    Opening = 'O',      // Opening
    Closing = 'C',      // Closing
    IpoAndHalted = 'H', // Ipo And Halted
    CrossNetwork = 'I', // Cross Network
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(CrossType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, CrossType value);

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
