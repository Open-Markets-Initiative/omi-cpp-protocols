#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case StockDirectoryMessage::message_type: return std::make_unique<StockDirectoryMessage>();
        case StockTradingActionMessage::message_type: return std::make_unique<StockTradingActionMessage>();
        case RegShoShortSalePriceTestRestrictedIndicatorMessage::message_type: return std::make_unique<RegShoShortSalePriceTestRestrictedIndicatorMessage>();
        case MarketParticipantPositionMessage::message_type: return std::make_unique<MarketParticipantPositionMessage>();
        case MwcbDeclineLevelMessage::message_type: return std::make_unique<MwcbDeclineLevelMessage>();
        case MwcbStatusMessage::message_type: return std::make_unique<MwcbStatusMessage>();
        case LuldAuctionCollarMessage::message_type: return std::make_unique<LuldAuctionCollarMessage>();
        case OperationalHaltMessage::message_type: return std::make_unique<OperationalHaltMessage>();
        case AddOrderNoMpidAttributionMessage::message_type: return std::make_unique<AddOrderNoMpidAttributionMessage>();
        case AddOrderMpidAttributionMessage::message_type: return std::make_unique<AddOrderMpidAttributionMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderExecutedWithPriceMessage::message_type: return std::make_unique<OrderExecutedWithPriceMessage>();
        case OrderCancelMessage::message_type: return std::make_unique<OrderCancelMessage>();
        case OrderDeleteMessage::message_type: return std::make_unique<OrderDeleteMessage>();
        case OrderReplaceMessage::message_type: return std::make_unique<OrderReplaceMessage>();
        case NonCrossTradeMessage::message_type: return std::make_unique<NonCrossTradeMessage>();
        case CrossTradeMessage::message_type: return std::make_unique<CrossTradeMessage>();
        case BrokenTradeMessage::message_type: return std::make_unique<BrokenTradeMessage>();
        case NetOrderImbalanceIndicatorMessage::message_type: return std::make_unique<NetOrderImbalanceIndicatorMessage>();
        case RetailInterestMessage::message_type: return std::make_unique<RetailInterestMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
