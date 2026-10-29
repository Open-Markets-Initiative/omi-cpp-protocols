#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::itch::v1_6 {

// Current trading state.
enum class TradingState : char {
    Trading = 'T',   // Trading
    Suspended = 'V', // Suspended
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingState value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingState value);

} // namespace jnx::jnxequities::pts::itch::v1_6
