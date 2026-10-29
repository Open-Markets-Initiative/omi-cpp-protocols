#include "Factory.hpp"

#include "definitions.hpp"

namespace jnx::jnxequities::pts::ouch::v1_11 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case DebugPacket::message_type: return std::make_unique<DebugPacket>();
        case LoginRequestPacket::message_type: return std::make_unique<LoginRequestPacket>();
        case UnsequencedDataPacket::message_type: return std::make_unique<UnsequencedDataPacket>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<UnsequencedMessage> UnsequencedMessageFactory::create(UnsequencedMessageCode code) {
    switch (code) {
        case EnterOrderMessage::message_type: return std::make_unique<EnterOrderMessage>();
        case ReplaceOrderMessage::message_type: return std::make_unique<ReplaceOrderMessage>();
        case CancelOrderMessage::message_type: return std::make_unique<CancelOrderMessage>();
        default: return std::make_unique<UnknownUnsequencedMessage>(code);
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
        case OrderAcceptedMessage::message_type: return std::make_unique<OrderAcceptedMessage>();
        case OrderReplacedMessage::message_type: return std::make_unique<OrderReplacedMessage>();
        case OrderCanceledMessage::message_type: return std::make_unique<OrderCanceledMessage>();
        case OrderAiqCanceledMessage::message_type: return std::make_unique<OrderAiqCanceledMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case OrderRejectedMessage::message_type: return std::make_unique<OrderRejectedMessage>();
        default: return std::make_unique<UnknownSequencedMessage>(code);
    }
}

} // namespace jnx::jnxequities::pts::ouch::v1_11
