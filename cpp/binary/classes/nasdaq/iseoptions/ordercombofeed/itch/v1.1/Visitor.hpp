#pragma once

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

class SystemEventMessage;
class ComplexStrategyDirectoryMessage;
class StrategyTradingActionMessage;
class StrategyOpenClosedMessage;
class ComplexStrategyOrderOnBookMessage;
class ComplexStrategyAuctionMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const ComplexStrategyDirectoryMessage&) {}
    virtual void visit(const StrategyTradingActionMessage&) {}
    virtual void visit(const StrategyOpenClosedMessage&) {}
    virtual void visit(const ComplexStrategyOrderOnBookMessage&) {}
    virtual void visit(const ComplexStrategyAuctionMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
