#include "MessageType.hpp"

namespace nyse::amexequities::integratedfeed::xdp::v2_1_g {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        case MessageType::SourceTimeReferenceMessage: return "Source Time Reference Message";
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
        case MessageType::AddOrderMessage: return "Add Order Message";
        case MessageType::ModifyOrderMessage: return "Modify Order Message";
        case MessageType::ReplaceOrderMessage: return "Replace Order Message";
        case MessageType::DeleteOrderMessage: return "Delete Order Message";
        case MessageType::TradeCancelMessage: return "Trade Cancel Message";
        case MessageType::CrossTradeMessage: return "Cross Trade Message";
        case MessageType::CrossCorrectionMessage: return "Cross Correction Message";
        case MessageType::RetailPriceImprovementMessage: return "Retail Price Improvement Message";
        case MessageType::AddOrderRefreshMessage: return "Add Order Refresh Message";
        case MessageType::ImbalanceMessage: return "Imbalance Message";
        case MessageType::OrderExecutionMessage: return "Order Execution Message";
        case MessageType::NonDisplayedTradeMessage: return "Non Displayed Trade Message";
        case MessageType::StockSummaryMessage: return "Stock Summary Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::amexequities::integratedfeed::xdp::v2_1_g
