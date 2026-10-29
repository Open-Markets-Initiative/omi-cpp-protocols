#pragma once

namespace nyse::arcaoptions::topfeed::pillar::v1_2_c {

class SequenceNumberResetMessage;
class TimeReferenceMessage;
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
class OutrightSeriesIndexMappingMessage;
class OptionsStatusMessage;
class OptionsQuoteMessage;
class OptionsTradeMessage;
class OptionsTradeCancelMessage;
class OptionsTradeCorrectionMessage;
class OptionsImbalanceMessage;
class SeriesRfqMessage;
class OutrightSeriesSummaryMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SequenceNumberResetMessage&) {}
    virtual void visit(const TimeReferenceMessage&) {}
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
    virtual void visit(const OutrightSeriesIndexMappingMessage&) {}
    virtual void visit(const OptionsStatusMessage&) {}
    virtual void visit(const OptionsQuoteMessage&) {}
    virtual void visit(const OptionsTradeMessage&) {}
    virtual void visit(const OptionsTradeCancelMessage&) {}
    virtual void visit(const OptionsTradeCorrectionMessage&) {}
    virtual void visit(const OptionsImbalanceMessage&) {}
    virtual void visit(const SeriesRfqMessage&) {}
    virtual void visit(const OutrightSeriesSummaryMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::arcaoptions::topfeed::pillar::v1_2_c
