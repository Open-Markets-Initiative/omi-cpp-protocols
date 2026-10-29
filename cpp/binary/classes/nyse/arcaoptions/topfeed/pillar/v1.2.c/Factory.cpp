#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        case TimeReferenceMessage::message_type: return std::make_unique<TimeReferenceMessage>();
        case SymbolIndexMappingMessage::message_type: return std::make_unique<SymbolIndexMappingMessage>();
        case RetransmissionRequestMessage::message_type: return std::make_unique<RetransmissionRequestMessage>();
        case RequestResponseMessage::message_type: return std::make_unique<RequestResponseMessage>();
        case HeartbeatResponseMessage::message_type: return std::make_unique<HeartbeatResponseMessage>();
        case SymbolIndexMappingRequestMessage::message_type: return std::make_unique<SymbolIndexMappingRequestMessage>();
        case RefreshRequestMessage::message_type: return std::make_unique<RefreshRequestMessage>();
        case MessageUnavailableMessage::message_type: return std::make_unique<MessageUnavailableMessage>();
        case SymbolClearMessage::message_type: return std::make_unique<SymbolClearMessage>();
        case SecurityStatusMessage::message_type: return std::make_unique<SecurityStatusMessage>();
        case RefreshHeaderMessage::message_type: return std::make_unique<RefreshHeaderMessage>();
        case OutrightSeriesIndexMappingMessage::message_type: return std::make_unique<OutrightSeriesIndexMappingMessage>();
        case OptionsStatusMessage::message_type: return std::make_unique<OptionsStatusMessage>();
        case OptionsQuoteMessage::message_type: return std::make_unique<OptionsQuoteMessage>();
        case OptionsTradeMessage::message_type: return std::make_unique<OptionsTradeMessage>();
        case OptionsTradeCancelMessage::message_type: return std::make_unique<OptionsTradeCancelMessage>();
        case OptionsTradeCorrectionMessage::message_type: return std::make_unique<OptionsTradeCorrectionMessage>();
        case OptionsImbalanceMessage::message_type: return std::make_unique<OptionsImbalanceMessage>();
        case SeriesRfqMessage::message_type: return std::make_unique<SeriesRfqMessage>();
        case OutrightSeriesSummaryMessage::message_type: return std::make_unique<OutrightSeriesSummaryMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
