#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class ImpliedMarketIndicator : std::uint8_t {
    NotImplied = 0,   // Not Implied
    ImpliedInOut = 3, // Implied In Out
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(ImpliedMarketIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, ImpliedMarketIndicator value);

} // namespace eurex::t7::eobi::fbe::v15_0
