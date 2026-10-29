#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Trade action indicator.
enum class TradeAction : std::uint8_t {
    Add = 2, // Add
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeAction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeAction value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
