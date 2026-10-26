#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

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
        case OptionsDirectoryMessage::message_type: return std::make_unique<OptionsDirectoryMessage>();
        case TradingActionMessage::message_type: return std::make_unique<TradingActionMessage>();
        case SecurityOpenClosedMessage::message_type: return std::make_unique<SecurityOpenClosedMessage>();
        case ShortBestBidAndAskUpdateMessage::message_type: return std::make_unique<ShortBestBidAndAskUpdateMessage>();
        case LongBestBidAndAskUpdateMessage::message_type: return std::make_unique<LongBestBidAndAskUpdateMessage>();
        case ShortBestAskUpdateMessage::message_type: return std::make_unique<ShortBestAskUpdateMessage>();
        case ShortBestBidUpdateMessage::message_type: return std::make_unique<ShortBestBidUpdateMessage>();
        case LongBestAskUpdateMessage::message_type: return std::make_unique<LongBestAskUpdateMessage>();
        case LongBestBidUpdateMessage::message_type: return std::make_unique<LongBestBidUpdateMessage>();
        case TradeReportMessage::message_type: return std::make_unique<TradeReportMessage>();
        case BrokenTradeReportMessage::message_type: return std::make_unique<BrokenTradeReportMessage>();
        case EndOfReplaySequenceMessage::message_type: return std::make_unique<EndOfReplaySequenceMessage>();
        default: return std::make_unique<UnknownSequencedMessage>(code);
    }
}

std::unique_ptr<PacketMessage> PacketMessageFactory::create(PacketMessageCode code) {
    switch (code) {
        case PayloadTimestampMessage::message_type: return std::make_unique<PayloadTimestampMessage>();
        case PayloadSystemEventMessage::message_type: return std::make_unique<PayloadSystemEventMessage>();
        case PayloadOptionsDirectoryMessage::message_type: return std::make_unique<PayloadOptionsDirectoryMessage>();
        case PayloadTradingActionMessage::message_type: return std::make_unique<PayloadTradingActionMessage>();
        case PayloadSecurityOpenClosedMessage::message_type: return std::make_unique<PayloadSecurityOpenClosedMessage>();
        case PayloadShortBestBidAndAskUpdateMessage::message_type: return std::make_unique<PayloadShortBestBidAndAskUpdateMessage>();
        case PayloadLongBestBidAndAskUpdateMessage::message_type: return std::make_unique<PayloadLongBestBidAndAskUpdateMessage>();
        case PayloadShortBestAskUpdateMessage::message_type: return std::make_unique<PayloadShortBestAskUpdateMessage>();
        case PayloadShortBestBidUpdateMessage::message_type: return std::make_unique<PayloadShortBestBidUpdateMessage>();
        case PayloadLongBestAskUpdateMessage::message_type: return std::make_unique<PayloadLongBestAskUpdateMessage>();
        case PayloadLongBestBidUpdateMessage::message_type: return std::make_unique<PayloadLongBestBidUpdateMessage>();
        case PayloadTradeReportMessage::message_type: return std::make_unique<PayloadTradeReportMessage>();
        case PayloadBrokenTradeReportMessage::message_type: return std::make_unique<PayloadBrokenTradeReportMessage>();
        default: return std::make_unique<UnknownPacketMessage>(code);
    }
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
