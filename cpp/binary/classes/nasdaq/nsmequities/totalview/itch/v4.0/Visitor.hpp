#pragma once

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

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
class StockDirectoryMessage;
class StockTradingActionMessage;
class MarketParticipantPositionMessage;
class AddOrderMessage;
class AddOrderWithMpidMessage;
class OrderExecutedMessage;
class OrderExecutedWithPriceMessage;
class OrderCancelMessage;
class OrderDeleteMessage;
class OrderReplaceMessage;
class TradeMessage;
class CrossTradeMessage;
class BrokenTradeMessage;
class NetOrderImbalanceIndicatorMessage;
class UnknownSequencedMessage;

// What the messages of the Sequenced Message dispatch are handed to,
// reached through the sequenced_message a SequencedDataPacket holds.
class SequencedMessageVisitor {
  public:
    virtual ~SequencedMessageVisitor() = default;

    virtual void visit(const TimestampMessage&) {}
    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const StockDirectoryMessage&) {}
    virtual void visit(const StockTradingActionMessage&) {}
    virtual void visit(const MarketParticipantPositionMessage&) {}
    virtual void visit(const AddOrderMessage&) {}
    virtual void visit(const AddOrderWithMpidMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderExecutedWithPriceMessage&) {}
    virtual void visit(const OrderCancelMessage&) {}
    virtual void visit(const OrderDeleteMessage&) {}
    virtual void visit(const OrderReplaceMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const CrossTradeMessage&) {}
    virtual void visit(const BrokenTradeMessage&) {}
    virtual void visit(const NetOrderImbalanceIndicatorMessage&) {}
    virtual void visit(const UnknownSequencedMessage&) {}
};

class PayloadTimestampMessage;
class PayloadSystemEventMessage;
class PayloadStockDirectoryMessage;
class PayloadStockTradingActionMessage;
class PayloadMarketParticipantPositionMessage;
class PayloadAddOrderMessage;
class PayloadAddOrderWithMpidMessage;
class PayloadOrderExecutedMessage;
class PayloadOrderExecutedWithPriceMessage;
class PayloadOrderCancelMessage;
class PayloadOrderDeleteMessage;
class PayloadOrderReplaceMessage;
class PayloadTradeMessage;
class PayloadCrossTradeMessage;
class PayloadBrokenTradeMessage;
class PayloadNetOrderImbalanceIndicatorMessage;
class UnknownPacketMessage;

// What the messages of the Payload dispatch are handed to,
// reached through the payload a Message holds.
class PacketMessageVisitor {
  public:
    virtual ~PacketMessageVisitor() = default;

    virtual void visit(const PayloadTimestampMessage&) {}
    virtual void visit(const PayloadSystemEventMessage&) {}
    virtual void visit(const PayloadStockDirectoryMessage&) {}
    virtual void visit(const PayloadStockTradingActionMessage&) {}
    virtual void visit(const PayloadMarketParticipantPositionMessage&) {}
    virtual void visit(const PayloadAddOrderMessage&) {}
    virtual void visit(const PayloadAddOrderWithMpidMessage&) {}
    virtual void visit(const PayloadOrderExecutedMessage&) {}
    virtual void visit(const PayloadOrderExecutedWithPriceMessage&) {}
    virtual void visit(const PayloadOrderCancelMessage&) {}
    virtual void visit(const PayloadOrderDeleteMessage&) {}
    virtual void visit(const PayloadOrderReplaceMessage&) {}
    virtual void visit(const PayloadTradeMessage&) {}
    virtual void visit(const PayloadCrossTradeMessage&) {}
    virtual void visit(const PayloadBrokenTradeMessage&) {}
    virtual void visit(const PayloadNetOrderImbalanceIndicatorMessage&) {}
    virtual void visit(const UnknownPacketMessage&) {}
};

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
