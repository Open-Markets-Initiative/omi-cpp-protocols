#pragma once

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

class MarketEventMessage;
class SymbolInformationMessage;
class SymbolStateMessage;
class NewOrderAddMessage;
class OrderPartialCancelMessage;
class OrderCancelAllMessage;
class OrderExecutedMessage;
class TradeMessage;
class TradeCancelMessage;
class TradeCorrectMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const MarketEventMessage&) {}
    virtual void visit(const SymbolInformationMessage&) {}
    virtual void visit(const SymbolStateMessage&) {}
    virtual void visit(const NewOrderAddMessage&) {}
    virtual void visit(const OrderPartialCancelMessage&) {}
    virtual void visit(const OrderCancelAllMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const TradeCancelMessage&) {}
    virtual void visit(const TradeCorrectMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
