#pragma once

namespace iex::iexequities::deepplus::iextp::v1_01 {

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
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to Packet::accept or Message::accept; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

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
    virtual void visit(const UnknownMessage&) {}
};

} // namespace iex::iexequities::deepplus::iextp::v1_01
