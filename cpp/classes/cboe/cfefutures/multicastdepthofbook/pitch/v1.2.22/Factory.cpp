#include "Factory.hpp"

#include "definitions.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case TimeReferenceMessage::message_type: return std::make_unique<TimeReferenceMessage>();
        case TimeMessage::message_type: return std::make_unique<TimeMessage>();
        case UnitClearMessage::message_type: return std::make_unique<UnitClearMessage>();
        case FuturesInstrumentDefinitionMessage::message_type: return std::make_unique<FuturesInstrumentDefinitionMessage>();
        case FuturesVarianceSymbolMappingMessage::message_type: return std::make_unique<FuturesVarianceSymbolMappingMessage>();
        case PriceLimitsMessage::message_type: return std::make_unique<PriceLimitsMessage>();
        case AddOrderLongMessage::message_type: return std::make_unique<AddOrderLongMessage>();
        case AddOrderShortMessage::message_type: return std::make_unique<AddOrderShortMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case ReduceSizeLongMessage::message_type: return std::make_unique<ReduceSizeLongMessage>();
        case ReduceSizeShortMessage::message_type: return std::make_unique<ReduceSizeShortMessage>();
        case ModifyOrderLongMessage::message_type: return std::make_unique<ModifyOrderLongMessage>();
        case ModifyOrderShortMessage::message_type: return std::make_unique<ModifyOrderShortMessage>();
        case DeleteOrderMessage::message_type: return std::make_unique<DeleteOrderMessage>();
        case TradeLongMessage::message_type: return std::make_unique<TradeLongMessage>();
        case TradeShortMessage::message_type: return std::make_unique<TradeShortMessage>();
        case TransactionBeginMessage::message_type: return std::make_unique<TransactionBeginMessage>();
        case TransactionEndMessage::message_type: return std::make_unique<TransactionEndMessage>();
        case TradeBreakMessage::message_type: return std::make_unique<TradeBreakMessage>();
        case SettlementMessage::message_type: return std::make_unique<SettlementMessage>();
        case OpenInterestMessage::message_type: return std::make_unique<OpenInterestMessage>();
        case EndOfDaySummaryMessage::message_type: return std::make_unique<EndOfDaySummaryMessage>();
        case TradingStatusMessage::message_type: return std::make_unique<TradingStatusMessage>();
        case EndOfSessionMessage::message_type: return std::make_unique<EndOfSessionMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
