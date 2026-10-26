#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

// Indicates the operational halt action for the security
enum class OperationalHaltAction : char {
    Halted = 'H',         // Halted
    TradingResumed = 'T', // Trading Resumed
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OperationalHaltAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OperationalHaltAction value);

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
