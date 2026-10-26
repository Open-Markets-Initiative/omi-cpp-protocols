#pragma once

namespace lseg::lse::level2mbo::gtp::v26_2 {

class SystemEventMessage;
class InstrumentDirectoryMessage;
class InstrumentStatusMessage;
class AddOrderMboMessage;
class AddOrderShortMboMessage;
class OrderBookClearMessage;
class TradeMessage;
class StatisticsMessage;
class StatisticsUpdateMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const InstrumentDirectoryMessage&) {}
    virtual void visit(const InstrumentStatusMessage&) {}
    virtual void visit(const AddOrderMboMessage&) {}
    virtual void visit(const AddOrderShortMboMessage&) {}
    virtual void visit(const OrderBookClearMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const StatisticsMessage&) {}
    virtual void visit(const StatisticsUpdateMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace lseg::lse::level2mbo::gtp::v26_2
