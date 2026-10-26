#include "Factory.hpp"

#include "definitions.hpp"

namespace iex::iexequities::tops::iextp::v1_66 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case SecurityDirectoryMessage::message_type: return std::make_unique<SecurityDirectoryMessage>();
        case TradingStatusMessage::message_type: return std::make_unique<TradingStatusMessage>();
        case RetailLiquidityIndicatorMessage::message_type: return std::make_unique<RetailLiquidityIndicatorMessage>();
        case OperationalHaltStatusMessage::message_type: return std::make_unique<OperationalHaltStatusMessage>();
        case ShortSalePriceTestStatusMessage::message_type: return std::make_unique<ShortSalePriceTestStatusMessage>();
        case QuoteUpdateMessage::message_type: return std::make_unique<QuoteUpdateMessage>();
        case TradeReportMessage::message_type: return std::make_unique<TradeReportMessage>();
        case OfficialPriceMessage::message_type: return std::make_unique<OfficialPriceMessage>();
        case TradeBreakMessage::message_type: return std::make_unique<TradeBreakMessage>();
        case AuctionInformationMessage::message_type: return std::make_unique<AuctionInformationMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace iex::iexequities::tops::iextp::v1_66
