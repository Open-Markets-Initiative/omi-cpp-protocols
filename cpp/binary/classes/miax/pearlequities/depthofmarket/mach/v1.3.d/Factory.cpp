#include "Factory.hpp"

#include "definitions.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case ApplicationMessage::message_type: return std::make_unique<ApplicationMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<Data> DataFactory::create(DataCode code) {
    switch (code) {
        case SystemTimeMessage::message_type: return std::make_unique<SystemTimeMessage>();
        case SymbolUpdateMessage::message_type: return std::make_unique<SymbolUpdateMessage>();
        case SystemStateMessage::message_type: return std::make_unique<SystemStateMessage>();
        case SecurityTradingStatusNotificationMessage::message_type: return std::make_unique<SecurityTradingStatusNotificationMessage>();
        case SymbolClearMessage::message_type: return std::make_unique<SymbolClearMessage>();
        case AddOrderMessage::message_type: return std::make_unique<AddOrderMessage>();
        case ModifyOrderMessage::message_type: return std::make_unique<ModifyOrderMessage>();
        case DeleteOrderMessage::message_type: return std::make_unique<DeleteOrderMessage>();
        case OrderExecutionMessage::message_type: return std::make_unique<OrderExecutionMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case TradeCancelMessage::message_type: return std::make_unique<TradeCancelMessage>();
        default: return std::make_unique<UnknownData>(code);
    }
}

std::unique_ptr<TcpMessage> TcpMessageFactory::create(TcpMessageCode code) {
    switch (code) {
        case SequencedDataPacket::message_type: return std::make_unique<SequencedDataPacket>();
        case UnsequencedDataPacket::message_type: return std::make_unique<UnsequencedDataPacket>();
        case LoginRequest::message_type: return std::make_unique<LoginRequest>();
        case LoginResponse::message_type: return std::make_unique<LoginResponse>();
        case SynchronizationComplete::message_type: return std::make_unique<SynchronizationComplete>();
        case RetransmissionRequest::message_type: return std::make_unique<RetransmissionRequest>();
        case LogoutRequest::message_type: return std::make_unique<LogoutRequest>();
        case GoodbyePacket::message_type: return std::make_unique<GoodbyePacket>();
        case TestPacket::message_type: return std::make_unique<TestPacket>();
        default: return std::make_unique<UnknownTcpMessage>(code);
    }
}

std::unique_ptr<UnsequencedMessage> UnsequencedMessageFactory::create(UnsequencedMessageCode code) {
    switch (code) {
        case RefreshRequestMessage::message_type: return std::make_unique<RefreshRequestMessage>();
        case RefreshResponseMessage::message_type: return std::make_unique<RefreshResponseMessage>();
        case EndOfRefreshNotificationMessage::message_type: return std::make_unique<EndOfRefreshNotificationMessage>();
        default: return std::make_unique<UnknownUnsequencedMessage>(code);
    }
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
