#pragma once

namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29 {

class TimeMessage;
class UnitClearMessage;
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
class TradeExpandedMessage;
class TradeBreakMessage;
class EndOfSession;
class TradingStatusMessage;
class AuctionUpdateMessage;
class AuctionSummaryMessage;
class RetailPriceImprovementMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const TimeMessage&) {}
    virtual void visit(const UnitClearMessage&) {}
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
    virtual void visit(const TradeExpandedMessage&) {}
    virtual void visit(const TradeBreakMessage&) {}
    virtual void visit(const EndOfSession&) {}
    virtual void visit(const TradingStatusMessage&) {}
    virtual void visit(const AuctionUpdateMessage&) {}
    virtual void visit(const AuctionSummaryMessage&) {}
    virtual void visit(const RetailPriceImprovementMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace cboe::byxequities::multicastdepthofbook::pitch::v2_41_29
