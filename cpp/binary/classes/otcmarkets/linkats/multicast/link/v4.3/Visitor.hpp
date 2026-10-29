#pragma once

namespace otcmarkets::linkats::multicast::link::v4_3 {

class StartOfSpinMessage;
class EndOfSpinMessage;
class MarketOpenMessage;
class MarketCloseMessage;
class SecurityMessage;
class QuoteMessage;
class QuoteUpdateMessage;
class InsideMessage;
class InsideUpdateMessage;
class ReferencePriceMessage;
class ReferencePriceUpdateMessage;
class ExtendedSecurityMessage;
class ExtendedSecurityNoCusipMessage;
class TradeMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const StartOfSpinMessage&) {}
    virtual void visit(const EndOfSpinMessage&) {}
    virtual void visit(const MarketOpenMessage&) {}
    virtual void visit(const MarketCloseMessage&) {}
    virtual void visit(const SecurityMessage&) {}
    virtual void visit(const QuoteMessage&) {}
    virtual void visit(const QuoteUpdateMessage&) {}
    virtual void visit(const InsideMessage&) {}
    virtual void visit(const InsideUpdateMessage&) {}
    virtual void visit(const ReferencePriceMessage&) {}
    virtual void visit(const ReferencePriceUpdateMessage&) {}
    virtual void visit(const ExtendedSecurityMessage&) {}
    virtual void visit(const ExtendedSecurityNoCusipMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace otcmarkets::linkats::multicast::link::v4_3
