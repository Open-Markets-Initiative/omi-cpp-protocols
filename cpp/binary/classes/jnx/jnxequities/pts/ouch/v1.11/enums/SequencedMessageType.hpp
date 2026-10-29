#pragma once

#include <cstdint>
#include <ostream>
#include <string_view>

namespace jnx::jnxequities::pts::ouch::v1_11 {

// Value identifying sequenced message type
enum class SequencedMessageType : char {
    SystemEventMessage = 'S',      // System Event Message
    OrderAcceptedMessage = 'A',    // Order Accepted Message
    OrderReplacedMessage = 'U',    // Order Replaced Message
    OrderCanceledMessage = 'C',    // Order Canceled Message
    OrderAiqCanceledMessage = 'D', // Order Aiq Canceled Message
    OrderExecutedMessage = 'E',    // Order Executed Message
    OrderRejectedMessage = 'J',    // Order Rejected Message
};

// The documented name of a code, or empty for one the specification does not list
std::string_view to_string(SequencedMessageType value);

// The documented name, or the raw code when there is none
std::ostream& operator<<(std::ostream& out, SequencedMessageType value);

} // namespace jnx::jnxequities::pts::ouch::v1_11
