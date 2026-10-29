#pragma once

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

class ApplicationMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const ApplicationMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

class SystemTimeMessage;
class SeriesUpdate;
class ComplexStrategyDefinitionMessage;
class SystemStateMessage;
class CompactComplexTopOfMarketBidMessage;
class CompactComplexTopOfMarketOfferMessage;
class WideComplexTopOfMarketBidMessage;
class WideComplexTopOfMarketOfferMessage;
class CompactComplexDoubleSidedTopOfMarketMessage;
class WideComplexDoubleSidedTopOfMarketMessage;
class StrategyTradeMessage;
class UnderlyingTradingStatusMessage;
class UnknownData;

// What the messages of the Data dispatch are handed to,
// reached through the data a ApplicationMessage holds.
class DataVisitor {
  public:
    virtual ~DataVisitor() = default;

    virtual void visit(const SystemTimeMessage&) {}
    virtual void visit(const SeriesUpdate&) {}
    virtual void visit(const ComplexStrategyDefinitionMessage&) {}
    virtual void visit(const SystemStateMessage&) {}
    virtual void visit(const CompactComplexTopOfMarketBidMessage&) {}
    virtual void visit(const CompactComplexTopOfMarketOfferMessage&) {}
    virtual void visit(const WideComplexTopOfMarketBidMessage&) {}
    virtual void visit(const WideComplexTopOfMarketOfferMessage&) {}
    virtual void visit(const CompactComplexDoubleSidedTopOfMarketMessage&) {}
    virtual void visit(const WideComplexDoubleSidedTopOfMarketMessage&) {}
    virtual void visit(const StrategyTradeMessage&) {}
    virtual void visit(const UnderlyingTradingStatusMessage&) {}
    virtual void visit(const UnknownData&) {}
};

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
