#pragma once

namespace jpx::tseequities::marketbyorder::flex::v1_1 {

class SecondsTimestampMessage;
class TradingStatusMessage;
class ExecutionSummaryMessage;
class AddOrderMessage;
class OrderExecutedMessage;
class OrderExecutedWithPriceMessage;
class OrderDeleteMessage;
class ResetMessage;
class CommunicationControlMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SecondsTimestampMessage&) {}
    virtual void visit(const TradingStatusMessage&) {}
    virtual void visit(const ExecutionSummaryMessage&) {}
    virtual void visit(const AddOrderMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderExecutedWithPriceMessage&) {}
    virtual void visit(const OrderDeleteMessage&) {}
    virtual void visit(const ResetMessage&) {}
    virtual void visit(const CommunicationControlMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

class LoginRequestMessage;
class LoginResultMessage;
class MessageResponseMessage;
class EndOfMessageMessage;
class UnknownTcpMessage;

// What the messages of the Tcp Payload dispatch are handed to,
// reached through the tcp_payload a TcpPacket holds.
class TcpMessageVisitor {
  public:
    virtual ~TcpMessageVisitor() = default;

    virtual void visit(const LoginRequestMessage&) {}
    virtual void visit(const LoginResultMessage&) {}
    virtual void visit(const MessageResponseMessage&) {}
    virtual void visit(const EndOfMessageMessage&) {}
    virtual void visit(const UnknownTcpMessage&) {}
};

} // namespace jpx::tseequities::marketbyorder::flex::v1_1
