#pragma once

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

class ApplicationMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const ApplicationMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

class SimpleInstrumentDefinitionMessage;
class ComplexInstrumentDefinitionMessage;
class SystemStateMessage;
class InstrumentTradingStatusNotificationMessage;
class BestBidAndOfferMessage;
class LastSaleMessage;
class TradeCancelMessage;
class UnknownData;

// What the messages of the Data dispatch are handed to,
// reached through the data a ApplicationMessage holds.
class DataVisitor {
  public:
    virtual ~DataVisitor() = default;

    virtual void visit(const SimpleInstrumentDefinitionMessage&) {}
    virtual void visit(const ComplexInstrumentDefinitionMessage&) {}
    virtual void visit(const SystemStateMessage&) {}
    virtual void visit(const InstrumentTradingStatusNotificationMessage&) {}
    virtual void visit(const BestBidAndOfferMessage&) {}
    virtual void visit(const LastSaleMessage&) {}
    virtual void visit(const TradeCancelMessage&) {}
    virtual void visit(const UnknownData&) {}
};

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
