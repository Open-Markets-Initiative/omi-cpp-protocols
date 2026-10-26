#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// The allowable values are:
enum class OpenState : char {
    Open = 'Y',   // Open
    Closed = 'N', // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OpenState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OpenState value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
