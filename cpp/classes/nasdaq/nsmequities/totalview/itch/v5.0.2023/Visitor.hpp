#pragma once

namespace nasdaq::nsmequities::totalview::itch::v5_0_2023 {

class SystemEventMessage;
class StockDirectoryMessage;
class StockTradingActionMessage;
class RegShoShortSalePriceTestRestrictedIndicatorMessage;
class MarketParticipantPositionMessage;
class MwcbDeclineLevelMessage;
class MwcbStatusLevelMessage;
class IpoQuotingPeriodUpdate;
class LuldAuctionCollarMessage;
class OperationalHaltMessage;
class AddOrderNoMpidAttributionMessage;
class AddOrderWithMpidAttributionMessage;
class OrderExecutedMessage;
class OrderExecutedWithPriceMessage;
class OrderCancelMessage;
class OrderDeleteMessage;
class OrderReplaceMessage;
class NonCrossTradeMessage;
class CrossTradeMessage;
class BrokenTradeMessage;
class NetOrderImbalanceIndicatorMessage;
class RetailPriceImprovementIndicatorMessage;
class DirectListingWithCapitalRaisePriceDiscoveryMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const StockDirectoryMessage&) {}
    virtual void visit(const StockTradingActionMessage&) {}
    virtual void visit(const RegShoShortSalePriceTestRestrictedIndicatorMessage&) {}
    virtual void visit(const MarketParticipantPositionMessage&) {}
    virtual void visit(const MwcbDeclineLevelMessage&) {}
    virtual void visit(const MwcbStatusLevelMessage&) {}
    virtual void visit(const IpoQuotingPeriodUpdate&) {}
    virtual void visit(const LuldAuctionCollarMessage&) {}
    virtual void visit(const OperationalHaltMessage&) {}
    virtual void visit(const AddOrderNoMpidAttributionMessage&) {}
    virtual void visit(const AddOrderWithMpidAttributionMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderExecutedWithPriceMessage&) {}
    virtual void visit(const OrderCancelMessage&) {}
    virtual void visit(const OrderDeleteMessage&) {}
    virtual void visit(const OrderReplaceMessage&) {}
    virtual void visit(const NonCrossTradeMessage&) {}
    virtual void visit(const CrossTradeMessage&) {}
    virtual void visit(const BrokenTradeMessage&) {}
    virtual void visit(const NetOrderImbalanceIndicatorMessage&) {}
    virtual void visit(const RetailPriceImprovementIndicatorMessage&) {}
    virtual void visit(const DirectListingWithCapitalRaisePriceDiscoveryMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nasdaq::nsmequities::totalview::itch::v5_0_2023
