#include "Factory.hpp"

#include "definitions.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SecondsMessage::message_type: return std::make_unique<SecondsMessage>();
        case EndOfBusinessTradeDateMessage::message_type: return std::make_unique<EndOfBusinessTradeDateMessage>();
        case FutureSymbolDirectoryMessage::message_type: return std::make_unique<FutureSymbolDirectoryMessage>();
        case OptionsSymbolDirectoryMessage::message_type: return std::make_unique<OptionsSymbolDirectoryMessage>();
        case CombinationSymbolDirectoryMessage::message_type: return std::make_unique<CombinationSymbolDirectoryMessage>();
        case BundlesSymbolDirectory::message_type: return std::make_unique<BundlesSymbolDirectory>();
        case OrderBookStateMessage::message_type: return std::make_unique<OrderBookStateMessage>();
        case AddOrderMessage::message_type: return std::make_unique<AddOrderMessage>();
        case OrderVolumeCancelledMessage::message_type: return std::make_unique<OrderVolumeCancelledMessage>();
        case OrderDeletedMessage::message_type: return std::make_unique<OrderDeletedMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case AuctionOrderExecutedMessage::message_type: return std::make_unique<AuctionOrderExecutedMessage>();
        case CombinationOrderExecutedMessage::message_type: return std::make_unique<CombinationOrderExecutedMessage>();
        case ImpliedOrderAddedMessage::message_type: return std::make_unique<ImpliedOrderAddedMessage>();
        case ImpliedOrderReplacedMessage::message_type: return std::make_unique<ImpliedOrderReplacedMessage>();
        case ImpliedOrderDeletedMessage::message_type: return std::make_unique<ImpliedOrderDeletedMessage>();
        case TradeExecutedMessage::message_type: return std::make_unique<TradeExecutedMessage>();
        case CombinationTradeExecutedMessage::message_type: return std::make_unique<CombinationTradeExecutedMessage>();
        case TradeCancellationMessage::message_type: return std::make_unique<TradeCancellationMessage>();
        case EquilibriumPriceMessage::message_type: return std::make_unique<EquilibriumPriceMessage>();
        case OpenHighLowLastTradeAdjustmentMessage::message_type: return std::make_unique<OpenHighLowLastTradeAdjustmentMessage>();
        case MarketSettlementMessage::message_type: return std::make_unique<MarketSettlementMessage>();
        case TextMessage::message_type: return std::make_unique<TextMessage>();
        case RequestForQuoteMessage::message_type: return std::make_unique<RequestForQuoteMessage>();
        case AnomalousOrderThresholdPublishMessage::message_type: return std::make_unique<AnomalousOrderThresholdPublishMessage>();
        case VolumeAndOpenInterestMessage::message_type: return std::make_unique<VolumeAndOpenInterestMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
