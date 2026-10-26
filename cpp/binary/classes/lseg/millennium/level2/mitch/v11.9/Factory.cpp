#include "Factory.hpp"

#include "definitions.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case TimeMessage::message_type: return std::make_unique<TimeMessage>();
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case SymbolDirectoryMessage::message_type: return std::make_unique<SymbolDirectoryMessage>();
        case SymbolStatusMessage::message_type: return std::make_unique<SymbolStatusMessage>();
        case AddOrderMessage::message_type: return std::make_unique<AddOrderMessage>();
        case AddAttributedOrderMessage::message_type: return std::make_unique<AddAttributedOrderMessage>();
        case OrderDeletedMessage::message_type: return std::make_unique<OrderDeletedMessage>();
        case OrderModifiedMessage::message_type: return std::make_unique<OrderModifiedMessage>();
        case OrderBookClearMessage::message_type: return std::make_unique<OrderBookClearMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderExecutedWithPriceSizeMessage::message_type: return std::make_unique<OrderExecutedWithPriceSizeMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case AuctionTradeMessage::message_type: return std::make_unique<AuctionTradeMessage>();
        case AuctionInfoMessage::message_type: return std::make_unique<AuctionInfoMessage>();
        case StatisticsMessage::message_type: return std::make_unique<StatisticsMessage>();
        case TopOfBookMessage::message_type: return std::make_unique<TopOfBookMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace lseg::millennium::level2::mitch::v11_9
