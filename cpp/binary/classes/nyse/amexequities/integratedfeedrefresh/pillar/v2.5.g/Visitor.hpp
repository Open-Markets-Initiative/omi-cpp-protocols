#pragma once

namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g {

class SequenceNumberResetMessage;
class SourceTimeReferenceMessage;
class SymbolIndexMappingMessage;
class SecurityStatusMessage;
class RefreshHeaderMessage;
class ImbalanceMessage;
class AddOrderRefreshMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SequenceNumberResetMessage&) {}
    virtual void visit(const SourceTimeReferenceMessage&) {}
    virtual void visit(const SymbolIndexMappingMessage&) {}
    virtual void visit(const SecurityStatusMessage&) {}
    virtual void visit(const RefreshHeaderMessage&) {}
    virtual void visit(const ImbalanceMessage&) {}
    virtual void visit(const AddOrderRefreshMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::amexequities::integratedfeedrefresh::pillar::v2_5_g
