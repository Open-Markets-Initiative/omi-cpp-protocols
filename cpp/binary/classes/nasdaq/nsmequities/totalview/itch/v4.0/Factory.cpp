#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

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
        case TimestampMessage::message_type: return std::make_unique<TimestampMessage>();
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case StockDirectoryMessage::message_type: return std::make_unique<StockDirectoryMessage>();
        case StockTradingActionMessage::message_type: return std::make_unique<StockTradingActionMessage>();
        case MarketParticipantPositionMessage::message_type: return std::make_unique<MarketParticipantPositionMessage>();
        case AddOrderMessage::message_type: return std::make_unique<AddOrderMessage>();
        case AddOrderWithMpidMessage::message_type: return std::make_unique<AddOrderWithMpidMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderExecutedWithPriceMessage::message_type: return std::make_unique<OrderExecutedWithPriceMessage>();
        case OrderCancelMessage::message_type: return std::make_unique<OrderCancelMessage>();
        case OrderDeleteMessage::message_type: return std::make_unique<OrderDeleteMessage>();
        case OrderReplaceMessage::message_type: return std::make_unique<OrderReplaceMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case CrossTradeMessage::message_type: return std::make_unique<CrossTradeMessage>();
        case BrokenTradeMessage::message_type: return std::make_unique<BrokenTradeMessage>();
        case NetOrderImbalanceIndicatorMessage::message_type: return std::make_unique<NetOrderImbalanceIndicatorMessage>();
        default: return std::make_unique<UnknownSequencedMessage>(code);
    }
}

std::unique_ptr<PacketMessage> PacketMessageFactory::create(PacketMessageCode code) {
    switch (code) {
        case PayloadTimestampMessage::message_type: return std::make_unique<PayloadTimestampMessage>();
        case PayloadSystemEventMessage::message_type: return std::make_unique<PayloadSystemEventMessage>();
        case PayloadStockDirectoryMessage::message_type: return std::make_unique<PayloadStockDirectoryMessage>();
        case PayloadStockTradingActionMessage::message_type: return std::make_unique<PayloadStockTradingActionMessage>();
        case PayloadMarketParticipantPositionMessage::message_type: return std::make_unique<PayloadMarketParticipantPositionMessage>();
        case PayloadAddOrderMessage::message_type: return std::make_unique<PayloadAddOrderMessage>();
        case PayloadAddOrderWithMpidMessage::message_type: return std::make_unique<PayloadAddOrderWithMpidMessage>();
        case PayloadOrderExecutedMessage::message_type: return std::make_unique<PayloadOrderExecutedMessage>();
        case PayloadOrderExecutedWithPriceMessage::message_type: return std::make_unique<PayloadOrderExecutedWithPriceMessage>();
        case PayloadOrderCancelMessage::message_type: return std::make_unique<PayloadOrderCancelMessage>();
        case PayloadOrderDeleteMessage::message_type: return std::make_unique<PayloadOrderDeleteMessage>();
        case PayloadOrderReplaceMessage::message_type: return std::make_unique<PayloadOrderReplaceMessage>();
        case PayloadTradeMessage::message_type: return std::make_unique<PayloadTradeMessage>();
        case PayloadCrossTradeMessage::message_type: return std::make_unique<PayloadCrossTradeMessage>();
        case PayloadBrokenTradeMessage::message_type: return std::make_unique<PayloadBrokenTradeMessage>();
        case PayloadNetOrderImbalanceIndicatorMessage::message_type: return std::make_unique<PayloadNetOrderImbalanceIndicatorMessage>();
        default: return std::make_unique<UnknownPacketMessage>(code);
    }
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
