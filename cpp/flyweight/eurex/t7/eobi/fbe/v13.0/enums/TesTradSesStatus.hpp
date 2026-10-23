#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class TesTradSesStatus : std::uint8_t {
    Halted = 1,   // Halted
    Open = 2,     // Open
    Closed = 3,   // Closed
    PreClose = 5, // Pre Close
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TesTradSesStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TesTradSesStatus value);

} // namespace eurex::t7::eobi::fbe::v13_0
