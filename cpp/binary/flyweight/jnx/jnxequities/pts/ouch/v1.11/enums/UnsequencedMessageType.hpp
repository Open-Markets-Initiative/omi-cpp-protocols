#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Value identifying unsequenced message type
enum class UnsequencedMessageType : char {
    EnterOrderMessage = 'O',   // Enter Order Message
    ReplaceOrderMessage = 'U', // Replace Order Message
    CancelOrderMessage = 'X',  // Cancel Order Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(UnsequencedMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, UnsequencedMessageType value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
