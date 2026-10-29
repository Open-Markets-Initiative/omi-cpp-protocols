#pragma once

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

class SystemEventMessage;
class ComplexStrategyDirectoryMessage;
class StrategyOpenClosedMessage;
class StrategyTradingActionMessage;
class StrategyBestBidAndAskUpdate;
class StrategyBestBidUpdate;
class StrategyBestAskUpdate;
class ComplexStrategyTickerMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const ComplexStrategyDirectoryMessage&) {}
    virtual void visit(const StrategyOpenClosedMessage&) {}
    virtual void visit(const StrategyTradingActionMessage&) {}
    virtual void visit(const StrategyBestBidAndAskUpdate&) {}
    virtual void visit(const StrategyBestBidUpdate&) {}
    virtual void visit(const StrategyBestAskUpdate&) {}
    virtual void visit(const ComplexStrategyTickerMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
