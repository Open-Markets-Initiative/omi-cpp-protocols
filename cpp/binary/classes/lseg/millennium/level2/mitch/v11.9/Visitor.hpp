#pragma once

namespace lseg::millennium::level2::mitch::v11_9 {

class TimeMessage;
class SystemEventMessage;
class SymbolDirectoryMessage;
class SymbolStatusMessage;
class AddOrderMessage;
class AddAttributedOrderMessage;
class OrderDeletedMessage;
class OrderModifiedMessage;
class OrderBookClearMessage;
class OrderExecutedMessage;
class OrderExecutedWithPriceSizeMessage;
class TradeMessage;
class AuctionTradeMessage;
class AuctionInfoMessage;
class StatisticsMessage;
class TopOfBookMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const TimeMessage&) {}
    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const SymbolDirectoryMessage&) {}
    virtual void visit(const SymbolStatusMessage&) {}
    virtual void visit(const AddOrderMessage&) {}
    virtual void visit(const AddAttributedOrderMessage&) {}
    virtual void visit(const OrderDeletedMessage&) {}
    virtual void visit(const OrderModifiedMessage&) {}
    virtual void visit(const OrderBookClearMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderExecutedWithPriceSizeMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const AuctionTradeMessage&) {}
    virtual void visit(const AuctionInfoMessage&) {}
    virtual void visit(const StatisticsMessage&) {}
    virtual void visit(const TopOfBookMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace lseg::millennium::level2::mitch::v11_9
