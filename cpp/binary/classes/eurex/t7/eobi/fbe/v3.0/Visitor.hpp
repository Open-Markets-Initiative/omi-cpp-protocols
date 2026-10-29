#pragma once

namespace eurex::t7::eobi::fbe::v3_0 {

class AddComplexInstrument;
class AuctionBbo;
class AuctionClearingPrice;
class CrossRequest;
class ExecutionSummary;
class FullOrderExecution;
class Heartbeat;
class InstrumentStateChange;
class InstrumentSummary;
class OrderAdd;
class OrderDelete;
class OrderMassDelete;
class OrderModify;
class OrderModifySamePrio;
class PartialOrderExecution;
class ProductStateChange;
class ProductSummary;
class QuoteRequest;
class SnapshotOrder;
class TopOfBook;
class TradeReport;
class TradeReversal;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const AddComplexInstrument&) {}
    virtual void visit(const AuctionBbo&) {}
    virtual void visit(const AuctionClearingPrice&) {}
    virtual void visit(const CrossRequest&) {}
    virtual void visit(const ExecutionSummary&) {}
    virtual void visit(const FullOrderExecution&) {}
    virtual void visit(const Heartbeat&) {}
    virtual void visit(const InstrumentStateChange&) {}
    virtual void visit(const InstrumentSummary&) {}
    virtual void visit(const OrderAdd&) {}
    virtual void visit(const OrderDelete&) {}
    virtual void visit(const OrderMassDelete&) {}
    virtual void visit(const OrderModify&) {}
    virtual void visit(const OrderModifySamePrio&) {}
    virtual void visit(const PartialOrderExecution&) {}
    virtual void visit(const ProductStateChange&) {}
    virtual void visit(const ProductSummary&) {}
    virtual void visit(const QuoteRequest&) {}
    virtual void visit(const SnapshotOrder&) {}
    virtual void visit(const TopOfBook&) {}
    virtual void visit(const TradeReport&) {}
    virtual void visit(const TradeReversal&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace eurex::t7::eobi::fbe::v3_0
