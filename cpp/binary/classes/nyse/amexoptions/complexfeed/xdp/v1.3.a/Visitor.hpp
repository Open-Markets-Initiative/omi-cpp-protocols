#pragma once

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

class ComplexQuoteMessage;
class ComplexTradeMessage;
class ComplexCrossingRfqMessage;
class ComplexCubeRfqMessage;
class ComplexStatusMessage;
class RefreshComplexQuoteMessage;
class RefreshComplexTradeMessage;
class ComplexSymbolDefinitionMessage;
class StreamIdMessage;
class SequenceNumberResetMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const ComplexQuoteMessage&) {}
    virtual void visit(const ComplexTradeMessage&) {}
    virtual void visit(const ComplexCrossingRfqMessage&) {}
    virtual void visit(const ComplexCubeRfqMessage&) {}
    virtual void visit(const ComplexStatusMessage&) {}
    virtual void visit(const RefreshComplexQuoteMessage&) {}
    virtual void visit(const RefreshComplexTradeMessage&) {}
    virtual void visit(const ComplexSymbolDefinitionMessage&) {}
    virtual void visit(const StreamIdMessage&) {}
    virtual void visit(const SequenceNumberResetMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
