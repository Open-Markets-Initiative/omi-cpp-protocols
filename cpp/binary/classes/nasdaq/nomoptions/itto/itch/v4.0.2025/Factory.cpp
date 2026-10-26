#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

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
        case OptionsDirectoryMessage::message_type: return std::make_unique<OptionsDirectoryMessage>();
        case TradingActionMessage::message_type: return std::make_unique<TradingActionMessage>();
        case SecurityOpenMessage::message_type: return std::make_unique<SecurityOpenMessage>();
        case AddOrderMessageShortMessageForm::message_type: return std::make_unique<AddOrderMessageShortMessageForm>();
        case AddOrderMessageLongFormMessage::message_type: return std::make_unique<AddOrderMessageLongFormMessage>();
        case AddQuoteMessageShortFormMessage::message_type: return std::make_unique<AddQuoteMessageShortFormMessage>();
        case AddQuoteMessageLongFormMessage::message_type: return std::make_unique<AddQuoteMessageLongFormMessage>();
        case SingleSideExecutedMessage::message_type: return std::make_unique<SingleSideExecutedMessage>();
        case SingleSideExecutedWithPriceMessage::message_type: return std::make_unique<SingleSideExecutedWithPriceMessage>();
        case OrderCancelMessage::message_type: return std::make_unique<OrderCancelMessage>();
        case SingleSideReplaceMessageShortForm::message_type: return std::make_unique<SingleSideReplaceMessageShortForm>();
        case SingleSideReplaceMessageLongForm::message_type: return std::make_unique<SingleSideReplaceMessageLongForm>();
        case SingleSideDeleteMessage::message_type: return std::make_unique<SingleSideDeleteMessage>();
        case SingleSideChangeMessage::message_type: return std::make_unique<SingleSideChangeMessage>();
        case QuoteReplaceMessageShortForm::message_type: return std::make_unique<QuoteReplaceMessageShortForm>();
        case QuoteReplaceMessageLongForm::message_type: return std::make_unique<QuoteReplaceMessageLongForm>();
        case QuoteDeleteMessage::message_type: return std::make_unique<QuoteDeleteMessage>();
        case OptionsTradeMessagesNonAuction::message_type: return std::make_unique<OptionsTradeMessagesNonAuction>();
        case OptionsCrossTradeMessage::message_type: return std::make_unique<OptionsCrossTradeMessage>();
        case BrokenTradeOrderExecutedMessage::message_type: return std::make_unique<BrokenTradeOrderExecutedMessage>();
        case NoiiMessage::message_type: return std::make_unique<NoiiMessage>();
        case EndOfReplaySequenceMessage::message_type: return std::make_unique<EndOfReplaySequenceMessage>();
        default: return std::make_unique<UnknownSequencedMessage>(code);
    }
}

std::unique_ptr<PacketMessage> PacketMessageFactory::create(PacketMessageCode code) {
    switch (code) {
        case UdpPayloadSystemEventMessage::message_type: return std::make_unique<UdpPayloadSystemEventMessage>();
        case UdpPayloadOptionsDirectoryMessage::message_type: return std::make_unique<UdpPayloadOptionsDirectoryMessage>();
        case UdpPayloadTradingActionMessage::message_type: return std::make_unique<UdpPayloadTradingActionMessage>();
        case UdpPayloadSecurityOpenMessage::message_type: return std::make_unique<UdpPayloadSecurityOpenMessage>();
        case UdpPayloadAddOrderMessageShortMessageForm::message_type: return std::make_unique<UdpPayloadAddOrderMessageShortMessageForm>();
        case UdpPayloadAddOrderMessageLongFormMessage::message_type: return std::make_unique<UdpPayloadAddOrderMessageLongFormMessage>();
        case UdpPayloadAddQuoteMessageShortFormMessage::message_type: return std::make_unique<UdpPayloadAddQuoteMessageShortFormMessage>();
        case UdpPayloadAddQuoteMessageLongFormMessage::message_type: return std::make_unique<UdpPayloadAddQuoteMessageLongFormMessage>();
        case UdpPayloadSingleSideExecutedMessage::message_type: return std::make_unique<UdpPayloadSingleSideExecutedMessage>();
        case UdpPayloadSingleSideExecutedWithPriceMessage::message_type: return std::make_unique<UdpPayloadSingleSideExecutedWithPriceMessage>();
        case UdpPayloadOrderCancelMessage::message_type: return std::make_unique<UdpPayloadOrderCancelMessage>();
        case UdpPayloadSingleSideReplaceMessageShortForm::message_type: return std::make_unique<UdpPayloadSingleSideReplaceMessageShortForm>();
        case UdpPayloadSingleSideReplaceMessageLongForm::message_type: return std::make_unique<UdpPayloadSingleSideReplaceMessageLongForm>();
        case UdpPayloadSingleSideDeleteMessage::message_type: return std::make_unique<UdpPayloadSingleSideDeleteMessage>();
        case UdpPayloadSingleSideChangeMessage::message_type: return std::make_unique<UdpPayloadSingleSideChangeMessage>();
        case UdpPayloadQuoteReplaceMessageShortForm::message_type: return std::make_unique<UdpPayloadQuoteReplaceMessageShortForm>();
        case UdpPayloadQuoteReplaceMessageLongForm::message_type: return std::make_unique<UdpPayloadQuoteReplaceMessageLongForm>();
        case UdpPayloadQuoteDeleteMessage::message_type: return std::make_unique<UdpPayloadQuoteDeleteMessage>();
        case UdpPayloadOptionsTradeMessagesNonAuction::message_type: return std::make_unique<UdpPayloadOptionsTradeMessagesNonAuction>();
        case UdpPayloadOptionsCrossTradeMessage::message_type: return std::make_unique<UdpPayloadOptionsCrossTradeMessage>();
        case UdpPayloadBrokenTradeOrderExecutedMessage::message_type: return std::make_unique<UdpPayloadBrokenTradeOrderExecutedMessage>();
        case UdpPayloadNoiiMessage::message_type: return std::make_unique<UdpPayloadNoiiMessage>();
        default: return std::make_unique<UnknownPacketMessage>(code);
    }
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
