#pragma once

namespace nyse::amexequities::integratedfeed::pillar::v2_5_g {

class SequenceNumberResetMessage;
class SourceTimeReferenceMessage;
class SymbolIndexMappingMessage;
class SymbolClearMessage;
class SecurityStatusMessage;
class AddOrderMessage;
class ModifyOrderMessage;
class DeleteOrderMessage;
class OrderExecutionMessage;
class ReplaceOrderMessage;
class ImbalanceMessage;
class AddOrderRefreshMessage;
class NonDisplayedTradeMessage;
class CrossTradeMessage;
class TradeCancelMessage;
class CrossCorrectionMessage;
class RetailPriceImprovementMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SequenceNumberResetMessage&) {}
    virtual void visit(const SourceTimeReferenceMessage&) {}
    virtual void visit(const SymbolIndexMappingMessage&) {}
    virtual void visit(const SymbolClearMessage&) {}
    virtual void visit(const SecurityStatusMessage&) {}
    virtual void visit(const AddOrderMessage&) {}
    virtual void visit(const ModifyOrderMessage&) {}
    virtual void visit(const DeleteOrderMessage&) {}
    virtual void visit(const OrderExecutionMessage&) {}
    virtual void visit(const ReplaceOrderMessage&) {}
    virtual void visit(const ImbalanceMessage&) {}
    virtual void visit(const AddOrderRefreshMessage&) {}
    virtual void visit(const NonDisplayedTradeMessage&) {}
    virtual void visit(const CrossTradeMessage&) {}
    virtual void visit(const TradeCancelMessage&) {}
    virtual void visit(const CrossCorrectionMessage&) {}
    virtual void visit(const RetailPriceImprovementMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::amexequities::integratedfeed::pillar::v2_5_g
