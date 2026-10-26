#include "Factory.hpp"

#include "definitions.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SecondsMessage::message_type: return std::make_unique<SecondsMessage>();
        case OrderBookDirectory::message_type: return std::make_unique<OrderBookDirectory>();
        case CombinationOrderbookLeg::message_type: return std::make_unique<CombinationOrderbookLeg>();
        case TickSizeTableEntry::message_type: return std::make_unique<TickSizeTableEntry>();
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case OrderBookStateMessage::message_type: return std::make_unique<OrderBookStateMessage>();
        case AddOrderNoMpid::message_type: return std::make_unique<AddOrderNoMpid>();
        case AddOrderWithMpid::message_type: return std::make_unique<AddOrderWithMpid>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderExecutedWithPriceMessage::message_type: return std::make_unique<OrderExecutedWithPriceMessage>();
        case OrderReplaceMessage::message_type: return std::make_unique<OrderReplaceMessage>();
        case OrderDeleteMessage::message_type: return std::make_unique<OrderDeleteMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case EquilibriumPriceUpdate::message_type: return std::make_unique<EquilibriumPriceUpdate>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
