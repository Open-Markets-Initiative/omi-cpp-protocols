#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case DebugPacket::message_type: return std::make_unique<DebugPacket>();
        case LoginRequestPacket::message_type: return std::make_unique<LoginRequestPacket>();
        case UnsequencedDataPacket::message_type: return std::make_unique<UnsequencedDataPacket>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<ServerMessage> ServerMessageFactory::create(ServerMessageCode code) {
    switch (code) {
        case ServerPayloadDebugPacket::message_type: return std::make_unique<ServerPayloadDebugPacket>();
        case LoginAcceptedPacket::message_type: return std::make_unique<LoginAcceptedPacket>();
        case LoginRejectedPacket::message_type: return std::make_unique<LoginRejectedPacket>();
        case SequencedDataPacket::message_type: return std::make_unique<SequencedDataPacket>();
        default: return std::make_unique<UnknownServerMessage>(code);
    }
}

std::unique_ptr<SequencedMessage> SequencedMessageFactory::create(SequencedMessageCode code) {
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
        default: return std::make_unique<UnknownSequencedMessage>(code);
    }
}

std::unique_ptr<PacketMessage> PacketMessageFactory::create(PacketMessageCode code) {
    switch (code) {
        case PayloadSystemEventMessage::message_type: return std::make_unique<PayloadSystemEventMessage>();
        case PayloadStockDirectoryMessage::message_type: return std::make_unique<PayloadStockDirectoryMessage>();
        case PayloadStockTradingActionMessage::message_type: return std::make_unique<PayloadStockTradingActionMessage>();
        case PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage::message_type: return std::make_unique<PayloadRegShoShortSalePriceTestRestrictedIndicatorMessage>();
        case PayloadMarketParticipantPositionMessage::message_type: return std::make_unique<PayloadMarketParticipantPositionMessage>();
        case PayloadMwcbDeclineLevelMessage::message_type: return std::make_unique<PayloadMwcbDeclineLevelMessage>();
        case PayloadMwcbStatusLevelMessage::message_type: return std::make_unique<PayloadMwcbStatusLevelMessage>();
        case PayloadIpoQuotingPeriodUpdate::message_type: return std::make_unique<PayloadIpoQuotingPeriodUpdate>();
        case PayloadLuldAuctionCollarMessage::message_type: return std::make_unique<PayloadLuldAuctionCollarMessage>();
        case PayloadOperationalHaltMessage::message_type: return std::make_unique<PayloadOperationalHaltMessage>();
        case PayloadAddOrderNoMpidAttributionMessage::message_type: return std::make_unique<PayloadAddOrderNoMpidAttributionMessage>();
        case PayloadAddOrderWithMpidAttributionMessage::message_type: return std::make_unique<PayloadAddOrderWithMpidAttributionMessage>();
        case PayloadOrderExecutedMessage::message_type: return std::make_unique<PayloadOrderExecutedMessage>();
        case PayloadOrderExecutedWithPriceMessage::message_type: return std::make_unique<PayloadOrderExecutedWithPriceMessage>();
        case PayloadOrderCancelMessage::message_type: return std::make_unique<PayloadOrderCancelMessage>();
        case PayloadOrderDeleteMessage::message_type: return std::make_unique<PayloadOrderDeleteMessage>();
        case PayloadOrderReplaceMessage::message_type: return std::make_unique<PayloadOrderReplaceMessage>();
        case PayloadNonCrossTradeMessage::message_type: return std::make_unique<PayloadNonCrossTradeMessage>();
        case PayloadCrossTradeMessage::message_type: return std::make_unique<PayloadCrossTradeMessage>();
        case PayloadBrokenTradeMessage::message_type: return std::make_unique<PayloadBrokenTradeMessage>();
        case PayloadNetOrderImbalanceIndicatorMessage::message_type: return std::make_unique<PayloadNetOrderImbalanceIndicatorMessage>();
        case PayloadRetailPriceImprovementIndicatorMessage::message_type: return std::make_unique<PayloadRetailPriceImprovementIndicatorMessage>();
        case PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage::message_type: return std::make_unique<PayloadDirectListingWithCapitalRaisePriceDiscoveryMessage>();
        default: return std::make_unique<UnknownPacketMessage>(code);
    }
}

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
