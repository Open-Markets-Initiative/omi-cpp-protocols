#pragma once

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

class SecondsMessage;
class OrderBookDirectory;
class CombinationOrderbookLeg;
class TickSizeTableEntry;
class SystemEventMessage;
class OrderBookStateMessage;
class AddOrderNoMpid;
class AddOrderWithMpid;
class OrderExecutedMessage;
class OrderExecutedWithPriceMessage;
class OrderReplaceMessage;
class OrderDeleteMessage;
class TradeMessage;
class EquilibriumPriceUpdate;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SecondsMessage&) {}
    virtual void visit(const OrderBookDirectory&) {}
    virtual void visit(const CombinationOrderbookLeg&) {}
    virtual void visit(const TickSizeTableEntry&) {}
    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const OrderBookStateMessage&) {}
    virtual void visit(const AddOrderNoMpid&) {}
    virtual void visit(const AddOrderWithMpid&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderExecutedWithPriceMessage&) {}
    virtual void visit(const OrderReplaceMessage&) {}
    virtual void visit(const OrderDeleteMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const EquilibriumPriceUpdate&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
