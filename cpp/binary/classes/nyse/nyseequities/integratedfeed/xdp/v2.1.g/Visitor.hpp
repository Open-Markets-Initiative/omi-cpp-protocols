#pragma once

namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g {

class SequenceNumberResetMessage;
class SourceTimeReferenceMessage;
class SymbolIndexMappingMessage;
class RetransmissionRequestMessage;
class RequestResponseMessage;
class HeartbeatResponseMessage;
class SymbolIndexMappingRequestMessage;
class RefreshRequestMessage;
class MessageUnavailableMessage;
class SymbolClearMessage;
class SecurityStatusMessage;
class RefreshHeaderMessage;
class AddOrderMessage;
class ModifyOrderMessage;
class ReplaceOrderMessage;
class DeleteOrderMessage;
class TradeCancelMessage;
class CrossTradeMessage;
class CrossCorrectionMessage;
class RetailPriceImprovementMessage;
class AddOrderRefreshMessage;
class ImbalanceMessage;
class OrderExecutionMessage;
class NonDisplayedTradeMessage;
class StockSummaryMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SequenceNumberResetMessage&) {}
    virtual void visit(const SourceTimeReferenceMessage&) {}
    virtual void visit(const SymbolIndexMappingMessage&) {}
    virtual void visit(const RetransmissionRequestMessage&) {}
    virtual void visit(const RequestResponseMessage&) {}
    virtual void visit(const HeartbeatResponseMessage&) {}
    virtual void visit(const SymbolIndexMappingRequestMessage&) {}
    virtual void visit(const RefreshRequestMessage&) {}
    virtual void visit(const MessageUnavailableMessage&) {}
    virtual void visit(const SymbolClearMessage&) {}
    virtual void visit(const SecurityStatusMessage&) {}
    virtual void visit(const RefreshHeaderMessage&) {}
    virtual void visit(const AddOrderMessage&) {}
    virtual void visit(const ModifyOrderMessage&) {}
    virtual void visit(const ReplaceOrderMessage&) {}
    virtual void visit(const DeleteOrderMessage&) {}
    virtual void visit(const TradeCancelMessage&) {}
    virtual void visit(const CrossTradeMessage&) {}
    virtual void visit(const CrossCorrectionMessage&) {}
    virtual void visit(const RetailPriceImprovementMessage&) {}
    virtual void visit(const AddOrderRefreshMessage&) {}
    virtual void visit(const ImbalanceMessage&) {}
    virtual void visit(const OrderExecutionMessage&) {}
    virtual void visit(const NonDisplayedTradeMessage&) {}
    virtual void visit(const StockSummaryMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::nyseequities::integratedfeed::xdp::v2_1_g
