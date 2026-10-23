#include "MessageType.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        case MessageType::SourceTimeReferenceMessage: return "Source Time Reference Message";
        case MessageType::SymbolIndexMappingMessage: return "Symbol Index Mapping Message";
        case MessageType::SymbolClearMessage: return "Symbol Clear Message";
        case MessageType::SecurityStatusMessage: return "Security Status Message";
        case MessageType::OutrightSeriesIndexMappingMessage: return "Outright Series Index Mapping Message";
        case MessageType::OptionsStatusMessage: return "Options Status Message";
        case MessageType::ComplexSeriesIndexMappingMessage: return "Complex Series Index Mapping Message";
        case MessageType::RetransmissionRequestMessage: return "Retransmission Request Message";
        case MessageType::RefreshHeaderMessage: return "Refresh Header Message";
        case MessageType::RefreshRequestMessage: return "Refresh Request Message";
        case MessageType::SymbolIndexMappingRequestMessage: return "Symbol Index Mapping Request Message";
        case MessageType::MessageUnavailableMessage: return "Message Unavailable Message";
        case MessageType::RequestResponseMessage: return "Request Response Message";
        case MessageType::HeartbeatResponseMessage: return "Heartbeat Response Message";
        case MessageType::OptionsAddOrderMessage: return "Options Add Order Message";
        case MessageType::OptionsModifyOrderMessage: return "Options Modify Order Message";
        case MessageType::OptionsDeleteOrderMessage: return "Options Delete Order Message";
        case MessageType::OptionsOrderExecutionMessage: return "Options Order Execution Message";
        case MessageType::OptionsReplaceOrderMessage: return "Options Replace Order Message";
        case MessageType::OptionsImbalanceMessage: return "Options Imbalance Message";
        case MessageType::OptionsAddOrderRefreshMessage: return "Options Add Order Refresh Message";
        case MessageType::OptionsSeriesRfqMessage: return "Options Series Rfq Message";
        case MessageType::OptionsNonDisplayedTradeMessage: return "Options Non Displayed Trade Message";
        case MessageType::OptionsCrossTradeMessage: return "Options Cross Trade Message";
        case MessageType::OptionsTradeCancelMessage: return "Options Trade Cancel Message";
        case MessageType::OptionsOutrightSeriesSummaryMessage: return "Options Outright Series Summary Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
