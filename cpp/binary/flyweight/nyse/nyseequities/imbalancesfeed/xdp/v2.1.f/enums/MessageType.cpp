#include "MessageType.hpp"

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        case MessageType::SymbolIndexMappingMessage: return "Symbol Index Mapping Message";
        case MessageType::RetransmissionRequestMessage: return "Retransmission Request Message";
        case MessageType::RequestResponseMessage: return "Request Response Message";
        case MessageType::HeartbeatResponseMessage: return "Heartbeat Response Message";
        case MessageType::SymbolIndexMappingRequestMessage: return "Symbol Index Mapping Request Message";
        case MessageType::RefreshRequestMessage: return "Refresh Request Message";
        case MessageType::MessageUnavailableMessage: return "Message Unavailable Message";
        case MessageType::SymbolClearMessage: return "Symbol Clear Message";
        case MessageType::SecurityStatusMessage: return "Security Status Message";
        case MessageType::RefreshHeaderMessage: return "Refresh Header Message";
        case MessageType::ImbalanceMessage: return "Imbalance Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_1_f
