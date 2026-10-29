#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        case SourceTimeReferenceMessage::message_type: return std::make_unique<SourceTimeReferenceMessage>();
        case SymbolIndexMappingMessage::message_type: return std::make_unique<SymbolIndexMappingMessage>();
        case SymbolClearMessage::message_type: return std::make_unique<SymbolClearMessage>();
        case SecurityStatusMessage::message_type: return std::make_unique<SecurityStatusMessage>();
        case MessageUnavailableMessage::message_type: return std::make_unique<MessageUnavailableMessage>();
        case AddOrderMessage::message_type: return std::make_unique<AddOrderMessage>();
        case ModifyOrderMessage::message_type: return std::make_unique<ModifyOrderMessage>();
        case DeleteOrderMessage::message_type: return std::make_unique<DeleteOrderMessage>();
        case OrderExecutionMessage::message_type: return std::make_unique<OrderExecutionMessage>();
        case ReplaceOrderMessage::message_type: return std::make_unique<ReplaceOrderMessage>();
        case ImbalanceMessage::message_type: return std::make_unique<ImbalanceMessage>();
        case AddOrderRefreshMessage::message_type: return std::make_unique<AddOrderRefreshMessage>();
        case NonDisplayedTradeMessage::message_type: return std::make_unique<NonDisplayedTradeMessage>();
        case CrossTradeMessage::message_type: return std::make_unique<CrossTradeMessage>();
        case TradeCancelMessage::message_type: return std::make_unique<TradeCancelMessage>();
        case CrossCorrectionMessage::message_type: return std::make_unique<CrossCorrectionMessage>();
        case RetailPriceImprovementMessage::message_type: return std::make_unique<RetailPriceImprovementMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::nyseequities::integratedfeedretransmission::pillar::v2_5_g
