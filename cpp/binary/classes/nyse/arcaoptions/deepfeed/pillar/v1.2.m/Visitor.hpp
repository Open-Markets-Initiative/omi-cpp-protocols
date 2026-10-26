#pragma once

namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m {

class SequenceNumberResetMessage;
class SourceTimeReferenceMessage;
class SymbolIndexMappingMessage;
class SymbolClearMessage;
class SecurityStatusMessage;
class OutrightSeriesIndexMappingMessage;
class OptionsStatusMessage;
class ComplexSeriesIndexMappingMessage;
class RetransmissionRequestMessage;
class RefreshHeaderMessage;
class RefreshRequestMessage;
class SymbolIndexMappingRequestMessage;
class MessageUnavailableMessage;
class RequestResponseMessage;
class HeartbeatResponseMessage;
class OptionsAddOrderMessage;
class OptionsModifyOrderMessage;
class OptionsDeleteOrderMessage;
class OptionsOrderExecutionMessage;
class OptionsReplaceOrderMessage;
class OptionsImbalanceMessage;
class OptionsAddOrderRefreshMessage;
class OptionsSeriesRfqMessage;
class OptionsNonDisplayedTradeMessage;
class OptionsCrossTradeMessage;
class OptionsTradeCancelMessage;
class OptionsOutrightSeriesSummaryMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SequenceNumberResetMessage&) {}
    virtual void visit(const SourceTimeReferenceMessage&) {}
    virtual void visit(const SymbolIndexMappingMessage&) {}
    virtual void visit(const SymbolClearMessage&) {}
    virtual void visit(const SecurityStatusMessage&) {}
    virtual void visit(const OutrightSeriesIndexMappingMessage&) {}
    virtual void visit(const OptionsStatusMessage&) {}
    virtual void visit(const ComplexSeriesIndexMappingMessage&) {}
    virtual void visit(const RetransmissionRequestMessage&) {}
    virtual void visit(const RefreshHeaderMessage&) {}
    virtual void visit(const RefreshRequestMessage&) {}
    virtual void visit(const SymbolIndexMappingRequestMessage&) {}
    virtual void visit(const MessageUnavailableMessage&) {}
    virtual void visit(const RequestResponseMessage&) {}
    virtual void visit(const HeartbeatResponseMessage&) {}
    virtual void visit(const OptionsAddOrderMessage&) {}
    virtual void visit(const OptionsModifyOrderMessage&) {}
    virtual void visit(const OptionsDeleteOrderMessage&) {}
    virtual void visit(const OptionsOrderExecutionMessage&) {}
    virtual void visit(const OptionsReplaceOrderMessage&) {}
    virtual void visit(const OptionsImbalanceMessage&) {}
    virtual void visit(const OptionsAddOrderRefreshMessage&) {}
    virtual void visit(const OptionsSeriesRfqMessage&) {}
    virtual void visit(const OptionsNonDisplayedTradeMessage&) {}
    virtual void visit(const OptionsCrossTradeMessage&) {}
    virtual void visit(const OptionsTradeCancelMessage&) {}
    virtual void visit(const OptionsOutrightSeriesSummaryMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::arcaoptions::deepfeed::pillar::v1_2_m
