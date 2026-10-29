#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

// The allocation model used by the MIAX Futures Onyx Trading Platform for the Product
enum class MatchAlgorithm : char {
    PriceThenTime = 'P', // Price Then Time
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MatchAlgorithm value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MatchAlgorithm value);

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
