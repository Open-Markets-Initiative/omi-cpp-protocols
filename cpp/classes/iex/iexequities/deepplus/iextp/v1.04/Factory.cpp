#include "Factory.hpp"

#include "definitions.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case SecurityDirectoryMessage::message_type: return std::make_unique<SecurityDirectoryMessage>();
        case TradingStatusMessage::message_type: return std::make_unique<TradingStatusMessage>();
        case RetailLiquidityIndicatorMessage::message_type: return std::make_unique<RetailLiquidityIndicatorMessage>();
        case OperationalHaltStatusMessage::message_type: return std::make_unique<OperationalHaltStatusMessage>();
        case ShortSalePriceTestStatusMessage::message_type: return std::make_unique<ShortSalePriceTestStatusMessage>();
        case SecurityEventMessage::message_type: return std::make_unique<SecurityEventMessage>();
        case AddOrderMessage::message_type: return std::make_unique<AddOrderMessage>();
        case OrderModifyMessage::message_type: return std::make_unique<OrderModifyMessage>();
        case OrderDeleteMessage::message_type: return std::make_unique<OrderDeleteMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case TradeBreakMessage::message_type: return std::make_unique<TradeBreakMessage>();
        case ClearBookMessage::message_type: return std::make_unique<ClearBookMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace iex::iexequities::deepplus::iextp::v1_04
