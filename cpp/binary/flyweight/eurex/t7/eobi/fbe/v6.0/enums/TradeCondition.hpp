#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v6_0 {

enum class TradeCondition : std::uint8_t {
    ImpliedTrade = 1,             // Implied Trade
    SystematicInternalizer = 153, // Systematic Internalizer
    MidpointPrice = 155,          // Midpoint Price
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(TradeCondition value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, TradeCondition value);

} // namespace eurex::t7::eobi::fbe::v6_0
