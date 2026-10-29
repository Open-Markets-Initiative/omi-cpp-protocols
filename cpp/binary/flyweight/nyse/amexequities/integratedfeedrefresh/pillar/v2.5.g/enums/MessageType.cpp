#include "MessageType.hpp"

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        case MessageType::SourceTimeReferenceMessage: return "Source Time Reference Message";
        case MessageType::SymbolIndexMappingMessage: return "Symbol Index Mapping Message";
        case MessageType::SecurityStatusMessage: return "Security Status Message";
        case MessageType::RefreshHeaderMessage: return "Refresh Header Message";
        case MessageType::ImbalanceMessage: return "Imbalance Message";
        case MessageType::AddOrderRefreshMessage: return "Add Order Refresh Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g
