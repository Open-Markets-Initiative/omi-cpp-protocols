#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::nationalequities::trades::pillar::v2_6 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        case SourceTimeReferenceMessage::message_type: return std::make_unique<SourceTimeReferenceMessage>();
        case SymbolIndexMappingMessage::message_type: return std::make_unique<SymbolIndexMappingMessage>();
        case SymbolClearMessage::message_type: return std::make_unique<SymbolClearMessage>();
        case SecurityStatusMessage::message_type: return std::make_unique<SecurityStatusMessage>();
        case RetransmissionRequestMessage::message_type: return std::make_unique<RetransmissionRequestMessage>();
        case SymbolIndexMappingRequestMessage::message_type: return std::make_unique<SymbolIndexMappingRequestMessage>();
        case RefreshRequestMessage::message_type: return std::make_unique<RefreshRequestMessage>();
        case MessageUnavailableMessage::message_type: return std::make_unique<MessageUnavailableMessage>();
        case RefreshHeaderMessage::message_type: return std::make_unique<RefreshHeaderMessage>();
        case RequestResponseMessage::message_type: return std::make_unique<RequestResponseMessage>();
        case HeartbeatResponseMessage::message_type: return std::make_unique<HeartbeatResponseMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case TradeCancelMessage::message_type: return std::make_unique<TradeCancelMessage>();
        case TradeCorrectionMessage::message_type: return std::make_unique<TradeCorrectionMessage>();
        case StockSummaryMessage::message_type: return std::make_unique<StockSummaryMessage>();
        case TrfFractionalTradeMessage::message_type: return std::make_unique<TrfFractionalTradeMessage>();
        case TrfTradeCancelMessage::message_type: return std::make_unique<TrfTradeCancelMessage>();
        case TrfFractionalTradeCorrectionMessage::message_type: return std::make_unique<TrfFractionalTradeCorrectionMessage>();
        case TrfFractionalPriorDayTradeMessage::message_type: return std::make_unique<TrfFractionalPriorDayTradeMessage>();
        case TrfFractionalPriorDayTradeCancelMessage::message_type: return std::make_unique<TrfFractionalPriorDayTradeCancelMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::nationalequities::trades::pillar::v2_6
