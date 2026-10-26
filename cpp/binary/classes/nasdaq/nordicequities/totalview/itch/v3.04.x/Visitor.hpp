#pragma once

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

class SystemEventMessage;
class OrderBookTradingActionMessage;
class OrderBookDirectoryMessage;
class AddOrderMessage;
class AddOrderMpidAttributionMessage;
class OrderExecutedMessage;
class OrderExecutedWithPriceMessage;
class OrderCancelMessage;
class OrderDeleteMessage;
class OrderBookFlushMessage;
class OrderReplaceMessage;
class TradeMessage;
class CrossTradeMessage;
class BrokenTradeMessage;
class NoiiMessage;
class MoiiMessage;
class ExecutionSummaryMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const OrderBookTradingActionMessage&) {}
    virtual void visit(const OrderBookDirectoryMessage&) {}
    virtual void visit(const AddOrderMessage&) {}
    virtual void visit(const AddOrderMpidAttributionMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderExecutedWithPriceMessage&) {}
    virtual void visit(const OrderCancelMessage&) {}
    virtual void visit(const OrderDeleteMessage&) {}
    virtual void visit(const OrderBookFlushMessage&) {}
    virtual void visit(const OrderReplaceMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const CrossTradeMessage&) {}
    virtual void visit(const BrokenTradeMessage&) {}
    virtual void visit(const NoiiMessage&) {}
    virtual void visit(const MoiiMessage&) {}
    virtual void visit(const ExecutionSummaryMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
