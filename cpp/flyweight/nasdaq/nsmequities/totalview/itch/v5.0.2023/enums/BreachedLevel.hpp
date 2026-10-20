#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Denotes the MWCB Level that was breached
enum class BreachedLevel : char {
    Level1 = '1', // Level 1
    Level2 = '2', // Level 2
    Level3 = '3', // Level 3
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(BreachedLevel value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, BreachedLevel value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
