#include "SequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(SequencedMessageType value) {
    switch (value) {
        case SequencedMessageType::SystemEventMessage: return "System Event Message";
        case SequencedMessageType::OrderAcceptedMessage: return "Order Accepted Message";
        case SequencedMessageType::OrderReplacedMessage: return "Order Replaced Message";
        case SequencedMessageType::OrderCanceledMessage: return "Order Canceled Message";
        case SequencedMessageType::OrderAiqCanceledMessage: return "Order Aiq Canceled Message";
        case SequencedMessageType::OrderExecutedMessage: return "Order Executed Message";
        case SequencedMessageType::OrderRejectedMessage: return "Order Rejected Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SequencedMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
