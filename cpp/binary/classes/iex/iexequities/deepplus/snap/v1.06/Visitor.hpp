#pragma once

namespace iex::iexequities::deepplus::snap::v1_06 {

class SnapshotRequestMessage;
class ErrorResponseMessage;
class SnapshotStartMessage;
class SnapshotDataMessage;
class SnapshotEndMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SnapshotRequestMessage&) {}
    virtual void visit(const ErrorResponseMessage&) {}
    virtual void visit(const SnapshotStartMessage&) {}
    virtual void visit(const SnapshotDataMessage&) {}
    virtual void visit(const SnapshotEndMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

class SystemEventMessage;
class SecurityDirectoryMessage;
class TradingStatusMessage;
class RetailLiquidityIndicatorMessage;
class OperationalHaltStatusMessage;
class ShortSalePriceTestStatusMessage;
class SecurityEventMessage;
class AddOrderMessage;
class OrderModifyMessage;
class OrderDeleteMessage;
class OrderExecutedMessage;
class TradeMessage;
class TradeBreakMessage;
class ClearBookMessage;
class UnknownIexTpMessageData;

// What the messages of the Iex Tp Message Data dispatch are handed to,
// reached through the iex_tp_message_data a SnapshotDataMessage holds.
class IexTpMessageDataVisitor {
  public:
    virtual ~IexTpMessageDataVisitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const SecurityDirectoryMessage&) {}
    virtual void visit(const TradingStatusMessage&) {}
    virtual void visit(const RetailLiquidityIndicatorMessage&) {}
    virtual void visit(const OperationalHaltStatusMessage&) {}
    virtual void visit(const ShortSalePriceTestStatusMessage&) {}
    virtual void visit(const SecurityEventMessage&) {}
    virtual void visit(const AddOrderMessage&) {}
    virtual void visit(const OrderModifyMessage&) {}
    virtual void visit(const OrderDeleteMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const TradeBreakMessage&) {}
    virtual void visit(const ClearBookMessage&) {}
    virtual void visit(const UnknownIexTpMessageData&) {}
};

} // namespace iex::iexequities::deepplus::snap::v1_06
