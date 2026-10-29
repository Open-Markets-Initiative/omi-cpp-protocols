#include "Factory.hpp"

#include "definitions.hpp"

namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case TimeMessage::message_type: return std::make_unique<TimeMessage>();
        case UnitClearMessage::message_type: return std::make_unique<UnitClearMessage>();
        case AddOrderLongMessage::message_type: return std::make_unique<AddOrderLongMessage>();
        case AddOrderShortMessage::message_type: return std::make_unique<AddOrderShortMessage>();
        case AddOrderExpandedMessage::message_type: return std::make_unique<AddOrderExpandedMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderExecutedAtPriceSizeMessage::message_type: return std::make_unique<OrderExecutedAtPriceSizeMessage>();
        case ReduceSizeLongMessage::message_type: return std::make_unique<ReduceSizeLongMessage>();
        case ReduceSizeShortMessage::message_type: return std::make_unique<ReduceSizeShortMessage>();
        case ModifyOrderLongMessage::message_type: return std::make_unique<ModifyOrderLongMessage>();
        case ModifyOrderShortMessage::message_type: return std::make_unique<ModifyOrderShortMessage>();
        case DeleteOrderMessage::message_type: return std::make_unique<DeleteOrderMessage>();
        case TradeLongMessage::message_type: return std::make_unique<TradeLongMessage>();
        case TradeShortMessage::message_type: return std::make_unique<TradeShortMessage>();
        case TradeExpandedMessage::message_type: return std::make_unique<TradeExpandedMessage>();
        case TradeBreakMessage::message_type: return std::make_unique<TradeBreakMessage>();
        case EndOfSessionMessage::message_type: return std::make_unique<EndOfSessionMessage>();
        case SymbolMappingMessage::message_type: return std::make_unique<SymbolMappingMessage>();
        case TradingStatusMessage::message_type: return std::make_unique<TradingStatusMessage>();
        case AuctionUpdateMessage::message_type: return std::make_unique<AuctionUpdateMessage>();
        case AuctionSummaryMessage::message_type: return std::make_unique<AuctionSummaryMessage>();
        case RetailPriceImprovementMessage::message_type: return std::make_unique<RetailPriceImprovementMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace cboe::bzxequities::multicastdepthofbook::pitch::v2_20_4
