#pragma once

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

class SequencedMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SequencedMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

class InstrumentDirectoryMessage;
class RegShoRestrictionMessage;
class SecurityTradingStatusMessage;
class TradingSessionStatusMessage;
class OrderAddedMessage;
class OrderDeletedMessage;
class OrderReducedMessage;
class OrderExecutedMessage;
class TradeMessage;
class BrokenTradeMessage;
class CorrectedTradeMessage;
class ClearBookMessage;
class SnapshotCompleteMessage;
class UnknownPayload;

// What the messages of the Payload dispatch are handed to,
// reached through the payload a SbeMessage holds.
class PayloadVisitor {
  public:
    virtual ~PayloadVisitor() = default;

    virtual void visit(const InstrumentDirectoryMessage&) {}
    virtual void visit(const RegShoRestrictionMessage&) {}
    virtual void visit(const SecurityTradingStatusMessage&) {}
    virtual void visit(const TradingSessionStatusMessage&) {}
    virtual void visit(const OrderAddedMessage&) {}
    virtual void visit(const OrderDeletedMessage&) {}
    virtual void visit(const OrderReducedMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const BrokenTradeMessage&) {}
    virtual void visit(const CorrectedTradeMessage&) {}
    virtual void visit(const ClearBookMessage&) {}
    virtual void visit(const SnapshotCompleteMessage&) {}
    virtual void visit(const UnknownPayload&) {}
};

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
