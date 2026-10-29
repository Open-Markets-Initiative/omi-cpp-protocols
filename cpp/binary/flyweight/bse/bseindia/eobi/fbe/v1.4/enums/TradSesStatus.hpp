#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// Miscellaneous state information.
enum class TradSesStatus : std::uint8_t {
    Halted = 1, // Halted
    Open = 2,   // Open
    Closed = 3, // Closed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradSesStatus value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradSesStatus value);

} // namespace bse::bseindia::eobi::fbe::v1_4
