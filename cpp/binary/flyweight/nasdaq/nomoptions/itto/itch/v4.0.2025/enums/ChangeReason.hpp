#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

enum class ChangeReason : char {
    User = 'U',    // User
    Reprice = 'R', // Reprice
    Suspend = 'S', // Suspend
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ChangeReason value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ChangeReason value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
