#include "Factory.hpp"

#include "definitions.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case MarketEventMessage::message_type: return std::make_unique<MarketEventMessage>();
        case SymbolInformationMessage::message_type: return std::make_unique<SymbolInformationMessage>();
        case SymbolStateMessage::message_type: return std::make_unique<SymbolStateMessage>();
        case NewOrderAddMessage::message_type: return std::make_unique<NewOrderAddMessage>();
        case OrderPartialCancelMessage::message_type: return std::make_unique<OrderPartialCancelMessage>();
        case OrderCancelAllMessage::message_type: return std::make_unique<OrderCancelAllMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case TradeCancelMessage::message_type: return std::make_unique<TradeCancelMessage>();
        case TradeCorrectMessage::message_type: return std::make_unique<TradeCorrectMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
