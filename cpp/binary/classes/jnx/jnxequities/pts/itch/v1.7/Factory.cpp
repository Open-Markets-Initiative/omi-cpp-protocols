#include "Factory.hpp"

#include "definitions.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

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
        case SecondsMessage::message_type: return std::make_unique<SecondsMessage>();
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case PriceTickSizeMessage::message_type: return std::make_unique<PriceTickSizeMessage>();
        case OrderbookDirectoryMessage::message_type: return std::make_unique<OrderbookDirectoryMessage>();
        case TradingStateMessage::message_type: return std::make_unique<TradingStateMessage>();
        case ShortSellingPriceRestrictionStateMessage::message_type: return std::make_unique<ShortSellingPriceRestrictionStateMessage>();
        case OrderAddedWithoutAttributesMessage::message_type: return std::make_unique<OrderAddedWithoutAttributesMessage>();
        case OrderAddedWithAttributesMessage::message_type: return std::make_unique<OrderAddedWithAttributesMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderDeletedMessage::message_type: return std::make_unique<OrderDeletedMessage>();
        case OrderReplacedMessage::message_type: return std::make_unique<OrderReplacedMessage>();
        default: return std::make_unique<UnknownSequencedMessage>(code);
    }
}

std::unique_ptr<PacketMessage> PacketMessageFactory::create(PacketMessageCode code) {
    switch (code) {
        case UdpPayloadSecondsMessage::message_type: return std::make_unique<UdpPayloadSecondsMessage>();
        case UdpPayloadSystemEventMessage::message_type: return std::make_unique<UdpPayloadSystemEventMessage>();
        case UdpPayloadPriceTickSizeMessage::message_type: return std::make_unique<UdpPayloadPriceTickSizeMessage>();
        case UdpPayloadOrderbookDirectoryMessage::message_type: return std::make_unique<UdpPayloadOrderbookDirectoryMessage>();
        case UdpPayloadTradingStateMessage::message_type: return std::make_unique<UdpPayloadTradingStateMessage>();
        case UdpPayloadShortSellingPriceRestrictionStateMessage::message_type: return std::make_unique<UdpPayloadShortSellingPriceRestrictionStateMessage>();
        case UdpPayloadOrderAddedWithoutAttributesMessage::message_type: return std::make_unique<UdpPayloadOrderAddedWithoutAttributesMessage>();
        case UdpPayloadOrderAddedWithAttributesMessage::message_type: return std::make_unique<UdpPayloadOrderAddedWithAttributesMessage>();
        case UdpPayloadOrderExecutedMessage::message_type: return std::make_unique<UdpPayloadOrderExecutedMessage>();
        case UdpPayloadOrderDeletedMessage::message_type: return std::make_unique<UdpPayloadOrderDeletedMessage>();
        case UdpPayloadOrderReplacedMessage::message_type: return std::make_unique<UdpPayloadOrderReplacedMessage>();
        default: return std::make_unique<UnknownPacketMessage>(code);
    }
}

} // namespace jnx::jnxequities::pts::itch::v1_7
