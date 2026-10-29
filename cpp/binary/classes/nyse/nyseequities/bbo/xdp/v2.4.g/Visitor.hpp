#pragma once

namespace nyse::nyseequities::bbo::xdp::v2_4_g {

class SequenceNumberResetMessage;
class SourceTimeReferenceMessage;
class SymbolIndexMappingMessage;
class RetransmissionRequestMessage;
class RequestResponseMessage;
class HeartbeatResponseMessage;
class SymbolIndexMappingRequestMessage;
class RefreshRequestMessage;
class MessageUnavailableMessage;
class SymbolClearMessage;
class TradingSessionChangeMessage;
class SecurityStatusMessage;
class RefreshHeaderMessage;
class QuoteMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SequenceNumberResetMessage&) {}
    virtual void visit(const SourceTimeReferenceMessage&) {}
    virtual void visit(const SymbolIndexMappingMessage&) {}
    virtual void visit(const RetransmissionRequestMessage&) {}
    virtual void visit(const RequestResponseMessage&) {}
    virtual void visit(const HeartbeatResponseMessage&) {}
    virtual void visit(const SymbolIndexMappingRequestMessage&) {}
    virtual void visit(const RefreshRequestMessage&) {}
    virtual void visit(const MessageUnavailableMessage&) {}
    virtual void visit(const SymbolClearMessage&) {}
    virtual void visit(const TradingSessionChangeMessage&) {}
    virtual void visit(const SecurityStatusMessage&) {}
    virtual void visit(const RefreshHeaderMessage&) {}
    virtual void visit(const QuoteMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::nyseequities::bbo::xdp::v2_4_g
