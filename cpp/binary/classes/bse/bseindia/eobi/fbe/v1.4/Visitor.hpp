#pragma once

namespace bse::bseindia::eobi::fbe::v1_4 {

class HeartbeatMessage;
class ProductSummaryMessage;
class SnapshotOrderMessage;
class InstrumentSummaryMessage;
class AuctionBestBidOfferMessage;
class AuctionClearingPriceMessage;
class TopOfBookMessage;
class OrderAddMessage;
class OrderModifyMessage;
class OrderModifySamePriorityMessage;
class OrderDeleteMessage;
class OrderMassDeleteMessage;
class PartialOrderExecutionMessage;
class FullOrderExecutionMessage;
class TradeReversalMessage;
class ExecutionSummaryMessage;
class InstrumentInfoMessage;
class LppRangeMessage;
class ProductStateChangeMessage;
class InstrumentStateChangeMessage;
class AddComplexInstrumentMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const HeartbeatMessage&) {}
    virtual void visit(const ProductSummaryMessage&) {}
    virtual void visit(const SnapshotOrderMessage&) {}
    virtual void visit(const InstrumentSummaryMessage&) {}
    virtual void visit(const AuctionBestBidOfferMessage&) {}
    virtual void visit(const AuctionClearingPriceMessage&) {}
    virtual void visit(const TopOfBookMessage&) {}
    virtual void visit(const OrderAddMessage&) {}
    virtual void visit(const OrderModifyMessage&) {}
    virtual void visit(const OrderModifySamePriorityMessage&) {}
    virtual void visit(const OrderDeleteMessage&) {}
    virtual void visit(const OrderMassDeleteMessage&) {}
    virtual void visit(const PartialOrderExecutionMessage&) {}
    virtual void visit(const FullOrderExecutionMessage&) {}
    virtual void visit(const TradeReversalMessage&) {}
    virtual void visit(const ExecutionSummaryMessage&) {}
    virtual void visit(const InstrumentInfoMessage&) {}
    virtual void visit(const LppRangeMessage&) {}
    virtual void visit(const ProductStateChangeMessage&) {}
    virtual void visit(const InstrumentStateChangeMessage&) {}
    virtual void visit(const AddComplexInstrumentMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace bse::bseindia::eobi::fbe::v1_4
