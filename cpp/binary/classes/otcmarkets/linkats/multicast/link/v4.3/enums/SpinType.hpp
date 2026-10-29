#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace otcmarkets::linkats::multicast::link::v4_3 {

// Spin type
enum class SpinType : std::uint8_t {
    Reference = 1,  // Reference
    MarketData = 2, // Market Data
    Opening = 3,    // Opening
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SpinType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SpinType value);

} // namespace otcmarkets::linkats::multicast::link::v4_3
