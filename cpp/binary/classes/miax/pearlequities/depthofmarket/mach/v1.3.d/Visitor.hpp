#pragma once

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

class ApplicationMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const ApplicationMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

class SystemTimeMessage;
class SymbolUpdateMessage;
class SystemStateMessage;
class SecurityTradingStatusNotificationMessage;
class SymbolClearMessage;
class AddOrderMessage;
class ModifyOrderMessage;
class DeleteOrderMessage;
class OrderExecutionMessage;
class TradeMessage;
class TradeCancelMessage;
class UnknownData;

// What the messages of the Data dispatch are handed to,
// reached through the data a ApplicationMessage holds.
class DataVisitor {
  public:
    virtual ~DataVisitor() = default;

    virtual void visit(const SystemTimeMessage&) {}
    virtual void visit(const SymbolUpdateMessage&) {}
    virtual void visit(const SystemStateMessage&) {}
    virtual void visit(const SecurityTradingStatusNotificationMessage&) {}
    virtual void visit(const SymbolClearMessage&) {}
    virtual void visit(const AddOrderMessage&) {}
    virtual void visit(const ModifyOrderMessage&) {}
    virtual void visit(const DeleteOrderMessage&) {}
    virtual void visit(const OrderExecutionMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const TradeCancelMessage&) {}
    virtual void visit(const UnknownData&) {}
};

class SequencedDataPacket;
class UnsequencedDataPacket;
class LoginRequest;
class LoginResponse;
class SynchronizationComplete;
class RetransmissionRequest;
class LogoutRequest;
class GoodbyePacket;
class TestPacket;
class UnknownTcpMessage;

// What the messages of the Esesm Payload dispatch are handed to,
// reached through the esesm_payload a EsesmTcpPacket holds.
class TcpMessageVisitor {
  public:
    virtual ~TcpMessageVisitor() = default;

    virtual void visit(const SequencedDataPacket&) {}
    virtual void visit(const UnsequencedDataPacket&) {}
    virtual void visit(const LoginRequest&) {}
    virtual void visit(const LoginResponse&) {}
    virtual void visit(const SynchronizationComplete&) {}
    virtual void visit(const RetransmissionRequest&) {}
    virtual void visit(const LogoutRequest&) {}
    virtual void visit(const GoodbyePacket&) {}
    virtual void visit(const TestPacket&) {}
    virtual void visit(const UnknownTcpMessage&) {}
};

class RefreshRequestMessage;
class RefreshResponseMessage;
class EndOfRefreshNotificationMessage;
class UnknownUnsequencedMessage;

// What the messages of the Unsequenced Message dispatch are handed to,
// reached through the unsequenced_message a UnsequencedDataPacket holds.
class UnsequencedMessageVisitor {
  public:
    virtual ~UnsequencedMessageVisitor() = default;

    virtual void visit(const RefreshRequestMessage&) {}
    virtual void visit(const RefreshResponseMessage&) {}
    virtual void visit(const EndOfRefreshNotificationMessage&) {}
    virtual void visit(const UnknownUnsequencedMessage&) {}
};

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
