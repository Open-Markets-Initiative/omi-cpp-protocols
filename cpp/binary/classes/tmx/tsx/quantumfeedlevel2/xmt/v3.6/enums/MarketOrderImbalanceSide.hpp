// Tmx.Tsx.QuantumFeedLevel2.Xmt.v3.6: enums/MarketOrderImbalanceSide.hpp
#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6 {

// Side Buy Or Sell Of The Market Order Imbalance Volume
enum class MarketOrderImbalanceSide : char {
    Buy = 'B',               // Buy
    Sell = 'S',              // Sell
    NoImbalanceExists = ' ', // No Imbalance Exists
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(MarketOrderImbalanceSide value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, MarketOrderImbalanceSide value);

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v3_6
