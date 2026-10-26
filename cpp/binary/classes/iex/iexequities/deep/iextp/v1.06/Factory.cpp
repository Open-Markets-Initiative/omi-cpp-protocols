#include "Factory.hpp"

#include "definitions.hpp"

namespace iex::iexequities::deep::iextp::v1_06 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case SecurityDirectoryMessage::message_type: return std::make_unique<SecurityDirectoryMessage>();
        case TradingStatusMessage::message_type: return std::make_unique<TradingStatusMessage>();
        case OperationalHaltStatusMessage::message_type: return std::make_unique<OperationalHaltStatusMessage>();
        case ShortSalePriceTestStatusMessage::message_type: return std::make_unique<ShortSalePriceTestStatusMessage>();
        case SecurityEventMessage::message_type: return std::make_unique<SecurityEventMessage>();
        case PriceLevelBuyUpdateMessage::message_type: return std::make_unique<PriceLevelBuyUpdateMessage>();
        case PriceLevelSellUpdateMessage::message_type: return std::make_unique<PriceLevelSellUpdateMessage>();
        case TradeReportMessage::message_type: return std::make_unique<TradeReportMessage>();
        case OfficialPriceMessage::message_type: return std::make_unique<OfficialPriceMessage>();
        case TradeBreakMessage::message_type: return std::make_unique<TradeBreakMessage>();
        case AuctionInformationMessage::message_type: return std::make_unique<AuctionInformationMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace iex::iexequities::deep::iextp::v1_06
