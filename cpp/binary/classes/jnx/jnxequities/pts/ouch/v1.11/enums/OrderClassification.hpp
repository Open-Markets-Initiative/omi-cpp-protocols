#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// High-frequency trading order classification
enum class OrderClassification : char {
    NonHft = '1',                  // Non Hft
    HftMarketMakingStrategy = '3', // Hft Market Making Strategy
    HftArbitrageStrategy = '4',    // Hft Arbitrage Strategy
    HftDirectionalStrategy = '5',  // Hft Directional Strategy
    HftOtherStrategy = '6',        // Hft Other Strategy
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(OrderClassification value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, OrderClassification value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
