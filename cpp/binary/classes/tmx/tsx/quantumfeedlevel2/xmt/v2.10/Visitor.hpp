// Tmx.Tsx.QuantumFeedLevel2.Xmt.v2.10: Visitor.hpp
#pragma once

namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10 {

class SymbolStatusMessage;
class OrderBookMessage;
class OrderBookTermsMessage;
class AssignCopOrdersMessage;
class AssignCopNoOrdersMessage;
class AssignLimitMessage;
class MarketStateUpdateMessage;
class MocImbalanceMessage;
class OrderBookedMessage;
class OrderBookedTermsMessage;
class OrderCancelledMessage;
class OrderCancelledTermsMessage;
class OrderPriceTimeAssignedMessage;
class OrderPriceTimeAssignedTermsMessage;
class StockStatusMessage;
class TradeReportMessage;
class TradeReportTermsMessage;
class TradeCancelledMessage;
class TradeCancelledTermsMessage;
class TradeCorrectionMessage;
class TradeCorrectionTermsMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SymbolStatusMessage&) {}
    virtual void visit(const OrderBookMessage&) {}
    virtual void visit(const OrderBookTermsMessage&) {}
    virtual void visit(const AssignCopOrdersMessage&) {}
    virtual void visit(const AssignCopNoOrdersMessage&) {}
    virtual void visit(const AssignLimitMessage&) {}
    virtual void visit(const MarketStateUpdateMessage&) {}
    virtual void visit(const MocImbalanceMessage&) {}
    virtual void visit(const OrderBookedMessage&) {}
    virtual void visit(const OrderBookedTermsMessage&) {}
    virtual void visit(const OrderCancelledMessage&) {}
    virtual void visit(const OrderCancelledTermsMessage&) {}
    virtual void visit(const OrderPriceTimeAssignedMessage&) {}
    virtual void visit(const OrderPriceTimeAssignedTermsMessage&) {}
    virtual void visit(const StockStatusMessage&) {}
    virtual void visit(const TradeReportMessage&) {}
    virtual void visit(const TradeReportTermsMessage&) {}
    virtual void visit(const TradeCancelledMessage&) {}
    virtual void visit(const TradeCancelledTermsMessage&) {}
    virtual void visit(const TradeCorrectionMessage&) {}
    virtual void visit(const TradeCorrectionTermsMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace tmx::tsx::quantumfeedlevel2::xmt::v2_10
