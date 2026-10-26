#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class TradingStyle : std::uint8_t {
    Regular = 1, // Regular
    Trftac = 2,  // Trftac
    Trftam = 3,  // Trftam
    Moc = 4,     // Moc
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradingStyle value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradingStyle value);

} // namespace eurex::t7::eobi::fbe::v15_0
