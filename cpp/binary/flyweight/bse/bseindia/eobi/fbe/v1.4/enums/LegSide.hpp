#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace bse::bseindia::eobi::fbe::v1_4 {

// The side of the individual leg of a strategy as defined in signature.
enum class LegSide : std::uint8_t {
    Buy = 1,  // Buy
    Sell = 2, // Sell
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(LegSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, LegSide value);

} // namespace bse::bseindia::eobi::fbe::v1_4
