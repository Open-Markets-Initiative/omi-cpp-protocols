#pragma once

namespace cboe::c1options::complex::pitch::v2_1_18 {

class TimeMessage;
class UnitClearMessage;
class TransactionBegin;
class TransactionEndMessage;
class ComplexInstrumentDefinitionExpandedMessage;
class SymbolMappingMessage;
class AddOrderLongMessage;
class AddOrderShortMessage;
class AddOrderExpandedMessage;
class OrderExecutedMessage;
class OrderExecutedAtPriceSizeMessage;
class ReduceSizeLongMessage;
class ReduceSizeShortMessage;
class ModifyOrderLongMessage;
class ModifyOrderShortMessage;
class DeleteOrderMessage;
class TradeLongMessage;
class TradeShortMessage;
class AuctionNotificationMessage;
class AuctionCancelMessage;
class AuctionTradeMessage;
class TradingStatusMessage;
class AuctionUpdateMessage;
class AuctionSummaryMessage;
class EndOfSessionMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const TimeMessage&) {}
    virtual void visit(const UnitClearMessage&) {}
    virtual void visit(const TransactionBegin&) {}
    virtual void visit(const TransactionEndMessage&) {}
    virtual void visit(const ComplexInstrumentDefinitionExpandedMessage&) {}
    virtual void visit(const SymbolMappingMessage&) {}
    virtual void visit(const AddOrderLongMessage&) {}
    virtual void visit(const AddOrderShortMessage&) {}
    virtual void visit(const AddOrderExpandedMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderExecutedAtPriceSizeMessage&) {}
    virtual void visit(const ReduceSizeLongMessage&) {}
    virtual void visit(const ReduceSizeShortMessage&) {}
    virtual void visit(const ModifyOrderLongMessage&) {}
    virtual void visit(const ModifyOrderShortMessage&) {}
    virtual void visit(const DeleteOrderMessage&) {}
    virtual void visit(const TradeLongMessage&) {}
    virtual void visit(const TradeShortMessage&) {}
    virtual void visit(const AuctionNotificationMessage&) {}
    virtual void visit(const AuctionCancelMessage&) {}
    virtual void visit(const AuctionTradeMessage&) {}
    virtual void visit(const TradingStatusMessage&) {}
    virtual void visit(const AuctionUpdateMessage&) {}
    virtual void visit(const AuctionSummaryMessage&) {}
    virtual void visit(const EndOfSessionMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace cboe::c1options::complex::pitch::v2_1_18
