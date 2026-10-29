#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3 {

// routingInstruction
enum class RoutingInstruction : std::uint8_t {
    RetailLiquidityTaker = 1, // Retail Liquidity Taker
    WaivedPriority = 2,       // Waived Priority
    BrokerOnly = 3,           // Broker Only
    BrokerOnlyRemoval = 4,    // Broker Only Removal
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(RoutingInstruction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, RoutingInstruction value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_3
