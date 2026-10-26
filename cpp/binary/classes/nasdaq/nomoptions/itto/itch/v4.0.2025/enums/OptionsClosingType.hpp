#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

// Denotes which System Event is used to trigger the option closing process.
enum class OptionsClosingType : char {
    Normal = 'N', // Normal
    Late = 'L',   // Late
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OptionsClosingType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OptionsClosingType value);

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
