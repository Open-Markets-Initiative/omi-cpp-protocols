#pragma once

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

class SystemEventMessage;
class StockDirectoryMessage;
class StockTradingActionMessage;
class RegShoRestrictionMessage;
class MwcbDeclineLevelMessage;
class MwcbBreachMessage;
class OperationalHaltMessage;
class BboQuotationMessage;
class PriceImprovementMessage;
class IpoQuotingPeriodUpdateMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const StockDirectoryMessage&) {}
    virtual void visit(const StockTradingActionMessage&) {}
    virtual void visit(const RegShoRestrictionMessage&) {}
    virtual void visit(const MwcbDeclineLevelMessage&) {}
    virtual void visit(const MwcbBreachMessage&) {}
    virtual void visit(const OperationalHaltMessage&) {}
    virtual void visit(const BboQuotationMessage&) {}
    virtual void visit(const PriceImprovementMessage&) {}
    virtual void visit(const IpoQuotingPeriodUpdateMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
