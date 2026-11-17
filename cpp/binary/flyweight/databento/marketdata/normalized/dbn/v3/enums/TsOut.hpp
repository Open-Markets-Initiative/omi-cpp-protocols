// Databento.MarketData.Normalized.Dbn.v3: enums/TsOut.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace databento::marketdata::normalized::dbn::v3 {

// Whether every record carries a ts_out trailer, the live gateway send timestamp
enum class TsOut : std::uint8_t {
    No = 0,  // No
    Yes = 1, // Yes
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TsOut value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TsOut value);

} // namespace databento::marketdata::normalized::dbn::v3
