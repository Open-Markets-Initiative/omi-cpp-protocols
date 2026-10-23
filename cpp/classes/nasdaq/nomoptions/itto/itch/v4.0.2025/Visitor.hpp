#pragma once

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

class DebugPacket;
class LoginRequestPacket;
class UnsequencedDataPacket;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const DebugPacket&) {}
    virtual void visit(const LoginRequestPacket&) {}
    virtual void visit(const UnsequencedDataPacket&) {}
    virtual void visit(const UnknownMessage&) {}
};

class ServerPayloadDebugPacket;
class LoginAcceptedPacket;
class LoginRejectedPacket;
class SequencedDataPacket;
class UnknownServerMessage;

// What the messages of the Server Payload dispatch are handed to,
// reached through the server_payload a ServerSoupBinTcpPacket holds.
class ServerMessageVisitor {
  public:
    virtual ~ServerMessageVisitor() = default;

    virtual void visit(const ServerPayloadDebugPacket&) {}
    virtual void visit(const LoginAcceptedPacket&) {}
    virtual void visit(const LoginRejectedPacket&) {}
    virtual void visit(const SequencedDataPacket&) {}
    virtual void visit(const UnknownServerMessage&) {}
};

class SystemEventMessage;
class OptionsDirectoryMessage;
class TradingActionMessage;
class SecurityOpenMessage;
class AddOrderMessageShortMessageForm;
class AddOrderMessageLongFormMessage;
class AddQuoteMessageShortFormMessage;
class AddQuoteMessageLongFormMessage;
class SingleSideExecutedMessage;
class SingleSideExecutedWithPriceMessage;
class OrderCancelMessage;
class SingleSideReplaceMessageShortForm;
class SingleSideReplaceMessageLongForm;
class SingleSideDeleteMessage;
class SingleSideChangeMessage;
class QuoteReplaceMessageShortForm;
class QuoteReplaceMessageLongForm;
class QuoteDeleteMessage;
class OptionsTradeMessagesNonAuction;
class OptionsCrossTradeMessage;
class BrokenTradeOrderExecutedMessage;
class NoiiMessage;
class EndOfReplaySequenceMessage;
class UnknownSequencedMessage;

// What the messages of the Sequenced Message dispatch are handed to,
// reached through the sequenced_message a SequencedDataPacket holds.
class SequencedMessageVisitor {
  public:
    virtual ~SequencedMessageVisitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const OptionsDirectoryMessage&) {}
    virtual void visit(const TradingActionMessage&) {}
    virtual void visit(const SecurityOpenMessage&) {}
    virtual void visit(const AddOrderMessageShortMessageForm&) {}
    virtual void visit(const AddOrderMessageLongFormMessage&) {}
    virtual void visit(const AddQuoteMessageShortFormMessage&) {}
    virtual void visit(const AddQuoteMessageLongFormMessage&) {}
    virtual void visit(const SingleSideExecutedMessage&) {}
    virtual void visit(const SingleSideExecutedWithPriceMessage&) {}
    virtual void visit(const OrderCancelMessage&) {}
    virtual void visit(const SingleSideReplaceMessageShortForm&) {}
    virtual void visit(const SingleSideReplaceMessageLongForm&) {}
    virtual void visit(const SingleSideDeleteMessage&) {}
    virtual void visit(const SingleSideChangeMessage&) {}
    virtual void visit(const QuoteReplaceMessageShortForm&) {}
    virtual void visit(const QuoteReplaceMessageLongForm&) {}
    virtual void visit(const QuoteDeleteMessage&) {}
    virtual void visit(const OptionsTradeMessagesNonAuction&) {}
    virtual void visit(const OptionsCrossTradeMessage&) {}
    virtual void visit(const BrokenTradeOrderExecutedMessage&) {}
    virtual void visit(const NoiiMessage&) {}
    virtual void visit(const EndOfReplaySequenceMessage&) {}
    virtual void visit(const UnknownSequencedMessage&) {}
};

class UdpPayloadSystemEventMessage;
class UdpPayloadOptionsDirectoryMessage;
class UdpPayloadTradingActionMessage;
class UdpPayloadSecurityOpenMessage;
class UdpPayloadAddOrderMessageShortMessageForm;
class UdpPayloadAddOrderMessageLongFormMessage;
class UdpPayloadAddQuoteMessageShortFormMessage;
class UdpPayloadAddQuoteMessageLongFormMessage;
class UdpPayloadSingleSideExecutedMessage;
class UdpPayloadSingleSideExecutedWithPriceMessage;
class UdpPayloadOrderCancelMessage;
class UdpPayloadSingleSideReplaceMessageShortForm;
class UdpPayloadSingleSideReplaceMessageLongForm;
class UdpPayloadSingleSideDeleteMessage;
class UdpPayloadSingleSideChangeMessage;
class UdpPayloadQuoteReplaceMessageShortForm;
class UdpPayloadQuoteReplaceMessageLongForm;
class UdpPayloadQuoteDeleteMessage;
class UdpPayloadOptionsTradeMessagesNonAuction;
class UdpPayloadOptionsCrossTradeMessage;
class UdpPayloadBrokenTradeOrderExecutedMessage;
class UdpPayloadNoiiMessage;
class UnknownPacketMessage;

// What the messages of the Udp Payload dispatch are handed to,
// reached through the udp_payload a Message holds.
class PacketMessageVisitor {
  public:
    virtual ~PacketMessageVisitor() = default;

    virtual void visit(const UdpPayloadSystemEventMessage&) {}
    virtual void visit(const UdpPayloadOptionsDirectoryMessage&) {}
    virtual void visit(const UdpPayloadTradingActionMessage&) {}
    virtual void visit(const UdpPayloadSecurityOpenMessage&) {}
    virtual void visit(const UdpPayloadAddOrderMessageShortMessageForm&) {}
    virtual void visit(const UdpPayloadAddOrderMessageLongFormMessage&) {}
    virtual void visit(const UdpPayloadAddQuoteMessageShortFormMessage&) {}
    virtual void visit(const UdpPayloadAddQuoteMessageLongFormMessage&) {}
    virtual void visit(const UdpPayloadSingleSideExecutedMessage&) {}
    virtual void visit(const UdpPayloadSingleSideExecutedWithPriceMessage&) {}
    virtual void visit(const UdpPayloadOrderCancelMessage&) {}
    virtual void visit(const UdpPayloadSingleSideReplaceMessageShortForm&) {}
    virtual void visit(const UdpPayloadSingleSideReplaceMessageLongForm&) {}
    virtual void visit(const UdpPayloadSingleSideDeleteMessage&) {}
    virtual void visit(const UdpPayloadSingleSideChangeMessage&) {}
    virtual void visit(const UdpPayloadQuoteReplaceMessageShortForm&) {}
    virtual void visit(const UdpPayloadQuoteReplaceMessageLongForm&) {}
    virtual void visit(const UdpPayloadQuoteDeleteMessage&) {}
    virtual void visit(const UdpPayloadOptionsTradeMessagesNonAuction&) {}
    virtual void visit(const UdpPayloadOptionsCrossTradeMessage&) {}
    virtual void visit(const UdpPayloadBrokenTradeOrderExecutedMessage&) {}
    virtual void visit(const UdpPayloadNoiiMessage&) {}
    virtual void visit(const UnknownPacketMessage&) {}
};

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
