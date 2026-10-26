#pragma once

namespace asx::asxderivatives::ntp::itch::v1_05 {

class SecondsMessage;
class EndOfBusinessTradeDateMessage;
class FutureSymbolDirectoryMessage;
class OptionsSymbolDirectoryMessage;
class CombinationSymbolDirectoryMessage;
class BundlesSymbolDirectory;
class OrderBookStateMessage;
class AddOrderMessage;
class OrderVolumeCancelledMessage;
class OrderDeletedMessage;
class OrderExecutedMessage;
class AuctionOrderExecutedMessage;
class CombinationOrderExecutedMessage;
class ImpliedOrderAddedMessage;
class ImpliedOrderReplacedMessage;
class ImpliedOrderDeletedMessage;
class TradeExecutedMessage;
class CombinationTradeExecutedMessage;
class TradeCancellationMessage;
class EquilibriumPriceMessage;
class OpenHighLowLastTradeAdjustmentMessage;
class MarketSettlementMessage;
class TextMessage;
class RequestForQuoteMessage;
class AnomalousOrderThresholdPublishMessage;
class VolumeAndOpenInterestMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SecondsMessage&) {}
    virtual void visit(const EndOfBusinessTradeDateMessage&) {}
    virtual void visit(const FutureSymbolDirectoryMessage&) {}
    virtual void visit(const OptionsSymbolDirectoryMessage&) {}
    virtual void visit(const CombinationSymbolDirectoryMessage&) {}
    virtual void visit(const BundlesSymbolDirectory&) {}
    virtual void visit(const OrderBookStateMessage&) {}
    virtual void visit(const AddOrderMessage&) {}
    virtual void visit(const OrderVolumeCancelledMessage&) {}
    virtual void visit(const OrderDeletedMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const AuctionOrderExecutedMessage&) {}
    virtual void visit(const CombinationOrderExecutedMessage&) {}
    virtual void visit(const ImpliedOrderAddedMessage&) {}
    virtual void visit(const ImpliedOrderReplacedMessage&) {}
    virtual void visit(const ImpliedOrderDeletedMessage&) {}
    virtual void visit(const TradeExecutedMessage&) {}
    virtual void visit(const CombinationTradeExecutedMessage&) {}
    virtual void visit(const TradeCancellationMessage&) {}
    virtual void visit(const EquilibriumPriceMessage&) {}
    virtual void visit(const OpenHighLowLastTradeAdjustmentMessage&) {}
    virtual void visit(const MarketSettlementMessage&) {}
    virtual void visit(const TextMessage&) {}
    virtual void visit(const RequestForQuoteMessage&) {}
    virtual void visit(const AnomalousOrderThresholdPublishMessage&) {}
    virtual void visit(const VolumeAndOpenInterestMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace asx::asxderivatives::ntp::itch::v1_05
