#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// TradeCond1 value
enum class TradeCond1 : char {
    RegularTrade = ' ', // Regular Trade
    LateReport = 'I',   // Late Report
    FloorTrade = 'R',   // Floor Trade
    SoSweepTrade = 'S', // So Sweep Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCond1 value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCond1 value);

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
