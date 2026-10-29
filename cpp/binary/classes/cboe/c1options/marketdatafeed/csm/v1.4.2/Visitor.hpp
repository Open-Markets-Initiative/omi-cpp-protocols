#pragma once

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

class SecurityDefinitionMessage;
class CurrentMarketRefreshMessage;
class MarketDataRefreshMessage;
class CurrentMarketUpdateMessage;
class RecapUpdateMessage;
class TickerMessage;
class ExpectedOpeningPriceAndSizeMessage;
class IndexValueMessage;
class SettlementValueMessage;
class SummaryMessage;
class MarketDataControlMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SecurityDefinitionMessage&) {}
    virtual void visit(const CurrentMarketRefreshMessage&) {}
    virtual void visit(const MarketDataRefreshMessage&) {}
    virtual void visit(const CurrentMarketUpdateMessage&) {}
    virtual void visit(const RecapUpdateMessage&) {}
    virtual void visit(const TickerMessage&) {}
    virtual void visit(const ExpectedOpeningPriceAndSizeMessage&) {}
    virtual void visit(const IndexValueMessage&) {}
    virtual void visit(const SettlementValueMessage&) {}
    virtual void visit(const SummaryMessage&) {}
    virtual void visit(const MarketDataControlMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
