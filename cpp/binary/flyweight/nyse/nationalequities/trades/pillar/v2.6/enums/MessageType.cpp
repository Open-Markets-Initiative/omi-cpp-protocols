#include "MessageType.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        case MessageType::SourceTimeReferenceMessage: return "Source Time Reference Message";
        case MessageType::SymbolIndexMappingMessage: return "Symbol Index Mapping Message";
        case MessageType::SymbolClearMessage: return "Symbol Clear Message";
        case MessageType::SecurityStatusMessage: return "Security Status Message";
        case MessageType::RetransmissionRequestMessage: return "Retransmission Request Message";
        case MessageType::SymbolIndexMappingRequestMessage: return "Symbol Index Mapping Request Message";
        case MessageType::RefreshRequestMessage: return "Refresh Request Message";
        case MessageType::MessageUnavailableMessage: return "Message Unavailable Message";
        case MessageType::RefreshHeaderMessage: return "Refresh Header Message";
        case MessageType::RequestResponseMessage: return "Request Response Message";
        case MessageType::HeartbeatResponseMessage: return "Heartbeat Response Message";
        case MessageType::TradeMessage: return "Trade Message";
        case MessageType::TradeCancelMessage: return "Trade Cancel Message";
        case MessageType::TradeCorrectionMessage: return "Trade Correction Message";
        case MessageType::StockSummaryMessage: return "Stock Summary Message";
        case MessageType::TrfFractionalTradeMessage: return "Trf Fractional Trade Message";
        case MessageType::TrfTradeCancelMessage: return "Trf Trade Cancel Message";
        case MessageType::TrfFractionalTradeCorrectionMessage: return "Trf Fractional Trade Correction Message";
        case MessageType::TrfFractionalPriorDayTradeMessage: return "Trf Fractional Prior Day Trade Message";
        case MessageType::TrfFractionalPriorDayTradeCancelMessage: return "Trf Fractional Prior Day Trade Cancel Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
