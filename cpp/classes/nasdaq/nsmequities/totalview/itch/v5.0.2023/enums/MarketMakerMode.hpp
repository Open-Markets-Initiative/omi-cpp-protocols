#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates the quoting participant's registration status in relation to SEC Rules 101 and 104
// of Regulation M
enum class MarketMakerMode : char {
    Normal = 'N',       // Normal
    Passive = 'P',      // Passive
    Syndicate = 'S',    // Syndicate
    PreSyndicate = 'R', // Pre Syndicate
    Penalty = 'L',      // Penalty
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketMakerMode value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketMakerMode value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
