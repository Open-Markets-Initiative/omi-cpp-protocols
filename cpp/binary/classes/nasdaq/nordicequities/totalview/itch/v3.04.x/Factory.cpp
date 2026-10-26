#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case OrderBookTradingActionMessage::message_type: return std::make_unique<OrderBookTradingActionMessage>();
        case OrderBookDirectoryMessage::message_type: return std::make_unique<OrderBookDirectoryMessage>();
        case AddOrderMessage::message_type: return std::make_unique<AddOrderMessage>();
        case AddOrderMpidAttributionMessage::message_type: return std::make_unique<AddOrderMpidAttributionMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderExecutedWithPriceMessage::message_type: return std::make_unique<OrderExecutedWithPriceMessage>();
        case OrderCancelMessage::message_type: return std::make_unique<OrderCancelMessage>();
        case OrderDeleteMessage::message_type: return std::make_unique<OrderDeleteMessage>();
        case OrderBookFlushMessage::message_type: return std::make_unique<OrderBookFlushMessage>();
        case OrderReplaceMessage::message_type: return std::make_unique<OrderReplaceMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case CrossTradeMessage::message_type: return std::make_unique<CrossTradeMessage>();
        case BrokenTradeMessage::message_type: return std::make_unique<BrokenTradeMessage>();
        case NoiiMessage::message_type: return std::make_unique<NoiiMessage>();
        case MoiiMessage::message_type: return std::make_unique<MoiiMessage>();
        case ExecutionSummaryMessage::message_type: return std::make_unique<ExecutionSummaryMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
