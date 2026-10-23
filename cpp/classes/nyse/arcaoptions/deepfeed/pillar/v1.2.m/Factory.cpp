#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        case SourceTimeReferenceMessage::message_type: return std::make_unique<SourceTimeReferenceMessage>();
        case SymbolIndexMappingMessage::message_type: return std::make_unique<SymbolIndexMappingMessage>();
        case SymbolClearMessage::message_type: return std::make_unique<SymbolClearMessage>();
        case SecurityStatusMessage::message_type: return std::make_unique<SecurityStatusMessage>();
        case OutrightSeriesIndexMappingMessage::message_type: return std::make_unique<OutrightSeriesIndexMappingMessage>();
        case OptionsStatusMessage::message_type: return std::make_unique<OptionsStatusMessage>();
        case ComplexSeriesIndexMappingMessage::message_type: return std::make_unique<ComplexSeriesIndexMappingMessage>();
        case RetransmissionRequestMessage::message_type: return std::make_unique<RetransmissionRequestMessage>();
        case RefreshHeaderMessage::message_type: return std::make_unique<RefreshHeaderMessage>();
        case RefreshRequestMessage::message_type: return std::make_unique<RefreshRequestMessage>();
        case SymbolIndexMappingRequestMessage::message_type: return std::make_unique<SymbolIndexMappingRequestMessage>();
        case MessageUnavailableMessage::message_type: return std::make_unique<MessageUnavailableMessage>();
        case RequestResponseMessage::message_type: return std::make_unique<RequestResponseMessage>();
        case HeartbeatResponseMessage::message_type: return std::make_unique<HeartbeatResponseMessage>();
        case OptionsAddOrderMessage::message_type: return std::make_unique<OptionsAddOrderMessage>();
        case OptionsModifyOrderMessage::message_type: return std::make_unique<OptionsModifyOrderMessage>();
        case OptionsDeleteOrderMessage::message_type: return std::make_unique<OptionsDeleteOrderMessage>();
        case OptionsOrderExecutionMessage::message_type: return std::make_unique<OptionsOrderExecutionMessage>();
        case OptionsReplaceOrderMessage::message_type: return std::make_unique<OptionsReplaceOrderMessage>();
        case OptionsImbalanceMessage::message_type: return std::make_unique<OptionsImbalanceMessage>();
        case OptionsAddOrderRefreshMessage::message_type: return std::make_unique<OptionsAddOrderRefreshMessage>();
        case OptionsSeriesRfqMessage::message_type: return std::make_unique<OptionsSeriesRfqMessage>();
        case OptionsNonDisplayedTradeMessage::message_type: return std::make_unique<OptionsNonDisplayedTradeMessage>();
        case OptionsCrossTradeMessage::message_type: return std::make_unique<OptionsCrossTradeMessage>();
        case OptionsTradeCancelMessage::message_type: return std::make_unique<OptionsTradeCancelMessage>();
        case OptionsOutrightSeriesSummaryMessage::message_type: return std::make_unique<OptionsOutrightSeriesSummaryMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
