#pragma once

namespace iex::iexequities::tops::iextp::v1_56 {

class QuoteUpdateMessage;
class TradeReportMessage;
class TradeBreakMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const QuoteUpdateMessage&) {}
    virtual void visit(const TradeReportMessage&) {}
    virtual void visit(const TradeBreakMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace iex::iexequities::tops::iextp::v1_56
