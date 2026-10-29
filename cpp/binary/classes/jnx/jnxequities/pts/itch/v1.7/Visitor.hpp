#pragma once

namespace jnx::jnxequities::pts::itch::v1_7 {

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

class SecondsMessage;
class SystemEventMessage;
class PriceTickSizeMessage;
class OrderbookDirectoryMessage;
class TradingStateMessage;
class ShortSellingPriceRestrictionStateMessage;
class OrderAddedWithoutAttributesMessage;
class OrderAddedWithAttributesMessage;
class OrderExecutedMessage;
class OrderDeletedMessage;
class OrderReplacedMessage;
class UnknownSequencedMessage;

// What the messages of the Sequenced Message dispatch are handed to,
// reached through the sequenced_message a SequencedDataPacket holds.
class SequencedMessageVisitor {
  public:
    virtual ~SequencedMessageVisitor() = default;

    virtual void visit(const SecondsMessage&) {}
    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const PriceTickSizeMessage&) {}
    virtual void visit(const OrderbookDirectoryMessage&) {}
    virtual void visit(const TradingStateMessage&) {}
    virtual void visit(const ShortSellingPriceRestrictionStateMessage&) {}
    virtual void visit(const OrderAddedWithoutAttributesMessage&) {}
    virtual void visit(const OrderAddedWithAttributesMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderDeletedMessage&) {}
    virtual void visit(const OrderReplacedMessage&) {}
    virtual void visit(const UnknownSequencedMessage&) {}
};

class UdpPayloadSecondsMessage;
class UdpPayloadSystemEventMessage;
class UdpPayloadPriceTickSizeMessage;
class UdpPayloadOrderbookDirectoryMessage;
class UdpPayloadTradingStateMessage;
class UdpPayloadShortSellingPriceRestrictionStateMessage;
class UdpPayloadOrderAddedWithoutAttributesMessage;
class UdpPayloadOrderAddedWithAttributesMessage;
class UdpPayloadOrderExecutedMessage;
class UdpPayloadOrderDeletedMessage;
class UdpPayloadOrderReplacedMessage;
class UnknownPacketMessage;

// What the messages of the Udp Payload dispatch are handed to,
// reached through the udp_payload a Message holds.
class PacketMessageVisitor {
  public:
    virtual ~PacketMessageVisitor() = default;

    virtual void visit(const UdpPayloadSecondsMessage&) {}
    virtual void visit(const UdpPayloadSystemEventMessage&) {}
    virtual void visit(const UdpPayloadPriceTickSizeMessage&) {}
    virtual void visit(const UdpPayloadOrderbookDirectoryMessage&) {}
    virtual void visit(const UdpPayloadTradingStateMessage&) {}
    virtual void visit(const UdpPayloadShortSellingPriceRestrictionStateMessage&) {}
    virtual void visit(const UdpPayloadOrderAddedWithoutAttributesMessage&) {}
    virtual void visit(const UdpPayloadOrderAddedWithAttributesMessage&) {}
    virtual void visit(const UdpPayloadOrderExecutedMessage&) {}
    virtual void visit(const UdpPayloadOrderDeletedMessage&) {}
    virtual void visit(const UdpPayloadOrderReplacedMessage&) {}
    virtual void visit(const UnknownPacketMessage&) {}
};

} // namespace jnx::jnxequities::pts::itch::v1_7
