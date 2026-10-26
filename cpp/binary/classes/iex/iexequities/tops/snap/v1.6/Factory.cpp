#include "Factory.hpp"

#include "definitions.hpp"

namespace iex::iexequities::tops::snap::v1_6 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SnapshotRequestMessage::message_type: return std::make_unique<SnapshotRequestMessage>();
        case ErrorResponseMessage::message_type: return std::make_unique<ErrorResponseMessage>();
        case SnapshotStartMessage::message_type: return std::make_unique<SnapshotStartMessage>();
        case SnapshotDataMessage::message_type: return std::make_unique<SnapshotDataMessage>();
        case SnapshotEndMessage::message_type: return std::make_unique<SnapshotEndMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<IexTpMessageData> IexTpMessageDataFactory::create(IexTpMessageDataCode code) {
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
        default: return std::make_unique<UnknownIexTpMessageData>(code);
    }
}

} // namespace iex::iexequities::tops::snap::v1_6
