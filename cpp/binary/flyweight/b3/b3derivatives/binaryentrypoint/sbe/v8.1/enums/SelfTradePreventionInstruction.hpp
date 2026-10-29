#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1 {

// selfTradePreventionInstruction
enum class SelfTradePreventionInstruction : std::uint8_t {
    None = 0,                 // None
    CancelAggressorOrder = 1, // Cancel Aggressor Order
    CancelRestingOrder = 2,   // Cancel Resting Order
    CancelBothOrders = 3,     // Cancel Both Orders
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SelfTradePreventionInstruction value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SelfTradePreventionInstruction value);

} // namespace b3::b3derivatives::binaryentrypoint::sbe::v8_1
