#pragma once

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

class TimeReferenceMessage;
class TimeMessage;
class UnitClearMessage;
class FuturesInstrumentDefinitionMessage;
class FuturesVarianceSymbolMappingMessage;
class PriceLimitsMessage;
class AddOrderLongMessage;
class AddOrderShortMessage;
class OrderExecutedMessage;
class ReduceSizeLongMessage;
class ReduceSizeShortMessage;
class ModifyOrderLongMessage;
class ModifyOrderShortMessage;
class DeleteOrderMessage;
class TradeLongMessage;
class TradeShortMessage;
class TransactionBeginMessage;
class TransactionEndMessage;
class TradeBreakMessage;
class SettlementMessage;
class OpenInterestMessage;
class EndOfDaySummaryMessage;
class TradingStatusMessage;
class EndOfSessionMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const TimeReferenceMessage&) {}
    virtual void visit(const TimeMessage&) {}
    virtual void visit(const UnitClearMessage&) {}
    virtual void visit(const FuturesInstrumentDefinitionMessage&) {}
    virtual void visit(const FuturesVarianceSymbolMappingMessage&) {}
    virtual void visit(const PriceLimitsMessage&) {}
    virtual void visit(const AddOrderLongMessage&) {}
    virtual void visit(const AddOrderShortMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const ReduceSizeLongMessage&) {}
    virtual void visit(const ReduceSizeShortMessage&) {}
    virtual void visit(const ModifyOrderLongMessage&) {}
    virtual void visit(const ModifyOrderShortMessage&) {}
    virtual void visit(const DeleteOrderMessage&) {}
    virtual void visit(const TradeLongMessage&) {}
    virtual void visit(const TradeShortMessage&) {}
    virtual void visit(const TransactionBeginMessage&) {}
    virtual void visit(const TransactionEndMessage&) {}
    virtual void visit(const TradeBreakMessage&) {}
    virtual void visit(const SettlementMessage&) {}
    virtual void visit(const OpenInterestMessage&) {}
    virtual void visit(const EndOfDaySummaryMessage&) {}
    virtual void visit(const TradingStatusMessage&) {}
    virtual void visit(const EndOfSessionMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
