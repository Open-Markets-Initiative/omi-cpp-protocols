#include "UnsequencedMessageType.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::string_view to_string(UnsequencedMessageType value) {
    switch (value) {
        case UnsequencedMessageType::EnterOrderMessage: return "Enter Order Message";
        case UnsequencedMessageType::ReplaceOrderMessage: return "Replace Order Message";
        case UnsequencedMessageType::CancelOrderMessage: return "Cancel Order Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, UnsequencedMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
