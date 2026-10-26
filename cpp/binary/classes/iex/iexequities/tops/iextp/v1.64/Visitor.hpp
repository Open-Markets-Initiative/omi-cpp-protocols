#pragma once

namespace iex::iexequities::tops::iextp::v1_64 {

class SystemEventMessage;
class SecurityDirectoryMessage;
class TradingStatusMessage;
class OperationalHaltStatusMessage;
class ShortSalePriceTestStatusMessage;
class SecurityEventMessage;
class QuoteUpdateMessage;
class TradeReportMessage;
class OfficialPriceMessage;
class TradeBreakMessage;
class AuctionInformationMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const SecurityDirectoryMessage&) {}
    virtual void visit(const TradingStatusMessage&) {}
    virtual void visit(const OperationalHaltStatusMessage&) {}
    virtual void visit(const ShortSalePriceTestStatusMessage&) {}
    virtual void visit(const SecurityEventMessage&) {}
    virtual void visit(const QuoteUpdateMessage&) {}
    virtual void visit(const TradeReportMessage&) {}
    virtual void visit(const OfficialPriceMessage&) {}
    virtual void visit(const TradeBreakMessage&) {}
    virtual void visit(const AuctionInformationMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace iex::iexequities::tops::iextp::v1_64
