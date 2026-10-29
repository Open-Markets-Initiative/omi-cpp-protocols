#pragma once

namespace nyse::nationalequities::trades::pillar::v2_6 {

class SequenceNumberResetMessage;
class SourceTimeReferenceMessage;
class SymbolIndexMappingMessage;
class SymbolClearMessage;
class SecurityStatusMessage;
class RetransmissionRequestMessage;
class SymbolIndexMappingRequestMessage;
class RefreshRequestMessage;
class MessageUnavailableMessage;
class RefreshHeaderMessage;
class RequestResponseMessage;
class HeartbeatResponseMessage;
class TradeMessage;
class TradeCancelMessage;
class TradeCorrectionMessage;
class StockSummaryMessage;
class TrfFractionalTradeMessage;
class TrfTradeCancelMessage;
class TrfFractionalTradeCorrectionMessage;
class TrfFractionalPriorDayTradeMessage;
class TrfFractionalPriorDayTradeCancelMessage;
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
    virtual void visit(const RetransmissionRequestMessage&) {}
    virtual void visit(const SymbolIndexMappingRequestMessage&) {}
    virtual void visit(const RefreshRequestMessage&) {}
    virtual void visit(const MessageUnavailableMessage&) {}
    virtual void visit(const RefreshHeaderMessage&) {}
    virtual void visit(const RequestResponseMessage&) {}
    virtual void visit(const HeartbeatResponseMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const TradeCancelMessage&) {}
    virtual void visit(const TradeCorrectionMessage&) {}
    virtual void visit(const StockSummaryMessage&) {}
    virtual void visit(const TrfFractionalTradeMessage&) {}
    virtual void visit(const TrfTradeCancelMessage&) {}
    virtual void visit(const TrfFractionalTradeCorrectionMessage&) {}
    virtual void visit(const TrfFractionalPriorDayTradeMessage&) {}
    virtual void visit(const TrfFractionalPriorDayTradeCancelMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nyse::nationalequities::trades::pillar::v2_6
