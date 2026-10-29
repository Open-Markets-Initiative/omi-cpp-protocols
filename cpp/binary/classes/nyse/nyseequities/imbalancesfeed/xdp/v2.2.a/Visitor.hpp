#pragma once

namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a {

class SequenceNumberResetMessage;
class SymbolIndexMappingMessage;
class RetransmissionRequestMessage;
class RequestResponseMessage;
class HeartbeatResponseMessage;
class SymbolIndexMappingRequestMessage;
class RefreshRequestMessage;
class MessageUnavailableMessage;
class SymbolClearMessage;
class SecurityStatusMessage;
class RefreshHeaderMessage;
class ImbalanceMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SequenceNumberResetMessage&) {}
    virtual void visit(const SymbolIndexMappingMessage&) {}
    virtual void visit(const RetransmissionRequestMessage&) {}
    virtual void visit(const RequestResponseMessage&) {}
    virtual void visit(const HeartbeatResponseMessage&) {}
    virtual void visit(const SymbolIndexMappingRequestMessage&) {}
    virtual void visit(const RefreshRequestMessage&) {}
    virtual void visit(const MessageUnavailableMessage&) {}
    virtual void visit(const SymbolClearMessage&) {}
    virtual void visit(const SecurityStatusMessage&) {}
    virtual void visit(const RefreshHeaderMessage&) {}
    virtual void visit(const ImbalanceMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::nyseequities::imbalancesfeed::xdp::v2_2_a
