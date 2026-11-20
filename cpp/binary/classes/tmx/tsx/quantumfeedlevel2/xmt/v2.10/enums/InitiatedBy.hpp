// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: enums/InitiatedBy.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

// Indicates Which Side Began The Trade Correction
enum class InitiatedBy : char {
    Buy = 'B',  // Buy
    Sell = 'S', // Sell
    Both = 'C', // Both
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(InitiatedBy value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, InitiatedBy value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
