#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case StockDirectoryMessage::message_type: return std::make_unique<StockDirectoryMessage>();
        case StockTradingActionMessage::message_type: return std::make_unique<StockTradingActionMessage>();
        case RegShoShortSalePriceTestRestrictedIndicatorMessage::message_type: return std::make_unique<RegShoShortSalePriceTestRestrictedIndicatorMessage>();
        case MarketParticipantPositionMessage::message_type: return std::make_unique<MarketParticipantPositionMessage>();
        case MwcbDeclineLevelMessage::message_type: return std::make_unique<MwcbDeclineLevelMessage>();
        case MwcbStatusLevelMessage::message_type: return std::make_unique<MwcbStatusLevelMessage>();
        case IpoQuotingPeriodUpdate::message_type: return std::make_unique<IpoQuotingPeriodUpdate>();
        case LuldAuctionCollarMessage::message_type: return std::make_unique<LuldAuctionCollarMessage>();
        case OperationalHaltMessage::message_type: return std::make_unique<OperationalHaltMessage>();
        case AddOrderNoMpidAttributionMessage::message_type: return std::make_unique<AddOrderNoMpidAttributionMessage>();
        case AddOrderWithMpidAttributionMessage::message_type: return std::make_unique<AddOrderWithMpidAttributionMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderExecutedWithPriceMessage::message_type: return std::make_unique<OrderExecutedWithPriceMessage>();
        case OrderCancelMessage::message_type: return std::make_unique<OrderCancelMessage>();
        case OrderDeleteMessage::message_type: return std::make_unique<OrderDeleteMessage>();
        case OrderReplaceMessage::message_type: return std::make_unique<OrderReplaceMessage>();
        case NonCrossTradeMessage::message_type: return std::make_unique<NonCrossTradeMessage>();
        case CrossTradeMessage::message_type: return std::make_unique<CrossTradeMessage>();
        case BrokenTradeMessage::message_type: return std::make_unique<BrokenTradeMessage>();
        case NetOrderImbalanceIndicatorMessage::message_type: return std::make_unique<NetOrderImbalanceIndicatorMessage>();
        case RetailPriceImprovementIndicatorMessage::message_type: return std::make_unique<RetailPriceImprovementIndicatorMessage>();
        case DirectListingWithCapitalRaisePriceDiscoveryMessage::message_type: return std::make_unique<DirectListingWithCapitalRaisePriceDiscoveryMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
