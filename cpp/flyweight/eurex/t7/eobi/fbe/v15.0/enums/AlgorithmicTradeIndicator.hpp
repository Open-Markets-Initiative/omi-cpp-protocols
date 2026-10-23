#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace eurex::t7::eobi::fbe::v15_0 {

enum class AlgorithmicTradeIndicator : std::uint8_t {
    AlgorithmicTrade = 1, // Algorithmic Trade
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(AlgorithmicTradeIndicator value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, AlgorithmicTradeIndicator value);

} // namespace eurex::t7::eobi::fbe::v15_0
