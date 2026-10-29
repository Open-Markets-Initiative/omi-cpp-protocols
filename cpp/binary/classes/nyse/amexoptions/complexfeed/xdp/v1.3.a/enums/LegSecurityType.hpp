#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

// Leg Security Type
enum class LegSecurityType : char {
    OptionsSeriesLeg = 'O', // Options Series Leg
    EquityStockLeg = 'E',   // Equity Stock Leg
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSecurityType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSecurityType value);

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
