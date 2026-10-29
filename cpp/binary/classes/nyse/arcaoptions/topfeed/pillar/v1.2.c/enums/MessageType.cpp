#include "MessageType.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SequenceNumberResetMessage: return "Sequence Number Reset Message";
        case MessageType::TimeReferenceMessage: return "Time Reference Message";
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
        case MessageType::OutrightSeriesIndexMappingMessage: return "Outright Series Index Mapping Message";
        case MessageType::OptionsStatusMessage: return "Options Status Message";
        case MessageType::OptionsQuoteMessage: return "Options Quote Message";
        case MessageType::OptionsTradeMessage: return "Options Trade Message";
        case MessageType::OptionsTradeCancelMessage: return "Options Trade Cancel Message";
        case MessageType::OptionsTradeCorrectionMessage: return "Options Trade Correction Message";
        case MessageType::OptionsImbalanceMessage: return "Options Imbalance Message";
        case MessageType::SeriesRfqMessage: return "Series Rfq Message";
        case MessageType::OutrightSeriesSummaryMessage: return "Outright Series Summary Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
