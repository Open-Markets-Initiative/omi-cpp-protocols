#pragma once

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

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

class TimestampMessage;
class SystemEventMessage;
class OptionsDirectoryMessage;
class TradingActionMessage;
class SecurityOpenClosedMessage;
class ShortBestBidAndAskUpdateMessage;
class LongBestBidAndAskUpdateMessage;
class ShortBestAskUpdateMessage;
class ShortBestBidUpdateMessage;
class LongBestAskUpdateMessage;
class LongBestBidUpdateMessage;
class TradeReportMessage;
class BrokenTradeReportMessage;
class EndOfReplaySequenceMessage;
class UnknownSequencedMessage;

// What the messages of the Sequenced Message dispatch are handed to,
// reached through the sequenced_message a SequencedDataPacket holds.
class SequencedMessageVisitor {
  public:
    virtual ~SequencedMessageVisitor() = default;

    virtual void visit(const TimestampMessage&) {}
    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const OptionsDirectoryMessage&) {}
    virtual void visit(const TradingActionMessage&) {}
    virtual void visit(const SecurityOpenClosedMessage&) {}
    virtual void visit(const ShortBestBidAndAskUpdateMessage&) {}
    virtual void visit(const LongBestBidAndAskUpdateMessage&) {}
    virtual void visit(const ShortBestAskUpdateMessage&) {}
    virtual void visit(const ShortBestBidUpdateMessage&) {}
    virtual void visit(const LongBestAskUpdateMessage&) {}
    virtual void visit(const LongBestBidUpdateMessage&) {}
    virtual void visit(const TradeReportMessage&) {}
    virtual void visit(const BrokenTradeReportMessage&) {}
    virtual void visit(const EndOfReplaySequenceMessage&) {}
    virtual void visit(const UnknownSequencedMessage&) {}
};

class PayloadTimestampMessage;
class PayloadSystemEventMessage;
class PayloadOptionsDirectoryMessage;
class PayloadTradingActionMessage;
class PayloadSecurityOpenClosedMessage;
class PayloadShortBestBidAndAskUpdateMessage;
class PayloadLongBestBidAndAskUpdateMessage;
class PayloadShortBestAskUpdateMessage;
class PayloadShortBestBidUpdateMessage;
class PayloadLongBestAskUpdateMessage;
class PayloadLongBestBidUpdateMessage;
class PayloadTradeReportMessage;
class PayloadBrokenTradeReportMessage;
class UnknownPacketMessage;

// What the messages of the Payload dispatch are handed to,
// reached through the payload a Message holds.
class PacketMessageVisitor {
  public:
    virtual ~PacketMessageVisitor() = default;

    virtual void visit(const PayloadTimestampMessage&) {}
    virtual void visit(const PayloadSystemEventMessage&) {}
    virtual void visit(const PayloadOptionsDirectoryMessage&) {}
    virtual void visit(const PayloadTradingActionMessage&) {}
    virtual void visit(const PayloadSecurityOpenClosedMessage&) {}
    virtual void visit(const PayloadShortBestBidAndAskUpdateMessage&) {}
    virtual void visit(const PayloadLongBestBidAndAskUpdateMessage&) {}
    virtual void visit(const PayloadShortBestAskUpdateMessage&) {}
    virtual void visit(const PayloadShortBestBidUpdateMessage&) {}
    virtual void visit(const PayloadLongBestAskUpdateMessage&) {}
    virtual void visit(const PayloadLongBestBidUpdateMessage&) {}
    virtual void visit(const PayloadTradeReportMessage&) {}
    virtual void visit(const PayloadBrokenTradeReportMessage&) {}
    virtual void visit(const UnknownPacketMessage&) {}
};

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
