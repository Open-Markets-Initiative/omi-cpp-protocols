#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        case SourceTimeReferenceMessage::message_type: return std::make_unique<SourceTimeReferenceMessage>();
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
        case AddOrderMessage::message_type: return std::make_unique<AddOrderMessage>();
        case ModifyOrderMessage::message_type: return std::make_unique<ModifyOrderMessage>();
        case ReplaceOrderMessage::message_type: return std::make_unique<ReplaceOrderMessage>();
        case DeleteOrderMessage::message_type: return std::make_unique<DeleteOrderMessage>();
        case OrderExecutionMessage::message_type: return std::make_unique<OrderExecutionMessage>();
        case NonDisplayedTradeMessage::message_type: return std::make_unique<NonDisplayedTradeMessage>();
        case TradeCancelMessage::message_type: return std::make_unique<TradeCancelMessage>();
        case RetailPriceImprovementMessage::message_type: return std::make_unique<RetailPriceImprovementMessage>();
        case CrossTradeMessage::message_type: return std::make_unique<CrossTradeMessage>();
        case CrossCorrectionMessage::message_type: return std::make_unique<CrossCorrectionMessage>();
        case ImbalanceMessage::message_type: return std::make_unique<ImbalanceMessage>();
        case AddOrderRefreshMessage::message_type: return std::make_unique<AddOrderRefreshMessage>();
        case StockSummaryMessage::message_type: return std::make_unique<StockSummaryMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_3_a
