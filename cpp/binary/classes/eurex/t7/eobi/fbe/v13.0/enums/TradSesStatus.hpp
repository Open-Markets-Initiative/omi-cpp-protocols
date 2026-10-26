#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v13_0 {

enum class TradSesStatus : std::uint8_t {
    Halted = 1, // Halted
    Open = 2,   // Open
    Closed = 3, // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradSesStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradSesStatus value);

} // namespace eurex::t7::eobi::fbe::v13_0
