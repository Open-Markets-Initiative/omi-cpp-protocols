#pragma once

namespace jnx::jnxequities::pts::ouch::v1_11 {

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

class EnterOrderMessage;
class ReplaceOrderMessage;
class CancelOrderMessage;
class UnknownUnsequencedMessage;

// What the messages of the Unsequenced Message dispatch are handed to,
// reached through the unsequenced_message a UnsequencedDataPacket holds.
class UnsequencedMessageVisitor {
  public:
    virtual ~UnsequencedMessageVisitor() = default;

    virtual void visit(const EnterOrderMessage&) {}
    virtual void visit(const ReplaceOrderMessage&) {}
    virtual void visit(const CancelOrderMessage&) {}
    virtual void visit(const UnknownUnsequencedMessage&) {}
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
class OrderAcceptedMessage;
class OrderReplacedMessage;
class OrderCanceledMessage;
class OrderAiqCanceledMessage;
class OrderExecutedMessage;
class OrderRejectedMessage;
class UnknownSequencedMessage;

// What the messages of the Sequenced Message dispatch are handed to,
// reached through the sequenced_message a SequencedDataPacket holds.
class SequencedMessageVisitor {
  public:
    virtual ~SequencedMessageVisitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const OrderAcceptedMessage&) {}
    virtual void visit(const OrderReplacedMessage&) {}
    virtual void visit(const OrderCanceledMessage&) {}
    virtual void visit(const OrderAiqCanceledMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderRejectedMessage&) {}
    virtual void visit(const UnknownSequencedMessage&) {}
};

} // namespace jnx::jnxequities::pts::ouch::v1_11
