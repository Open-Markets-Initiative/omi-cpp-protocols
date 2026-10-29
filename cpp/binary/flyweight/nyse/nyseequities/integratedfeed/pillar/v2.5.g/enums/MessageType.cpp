#include "MessageType.hpp"

namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        case MessageType::SourceTimeReferenceMessage: return "Source Time Reference Message";
        case MessageType::SymbolIndexMappingMessage: return "Symbol Index Mapping Message";
        case MessageType::SymbolClearMessage: return "Symbol Clear Message";
        case MessageType::SecurityStatusMessage: return "Security Status Message";
        case MessageType::AddOrderMessage: return "Add Order Message";
        case MessageType::ModifyOrderMessage: return "Modify Order Message";
        case MessageType::DeleteOrderMessage: return "Delete Order Message";
        case MessageType::OrderExecutionMessage: return "Order Execution Message";
        case MessageType::ReplaceOrderMessage: return "Replace Order Message";
        case MessageType::ImbalanceMessage: return "Imbalance Message";
        case MessageType::AddOrderRefreshMessage: return "Add Order Refresh Message";
        case MessageType::NonDisplayedTradeMessage: return "Non Displayed Trade Message";
        case MessageType::CrossTradeMessage: return "Cross Trade Message";
        case MessageType::TradeCancelMessage: return "Trade Cancel Message";
        case MessageType::CrossCorrectionMessage: return "Cross Correction Message";
        case MessageType::RetailPriceImprovementMessage: return "Retail Price Improvement Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::nyseequities::integratedfeed::pillar::v2_5_g
