#pragma once

namespace jnx::jnxequities::pts::itch::v1_6 {

class SecondsMessage;
class SystemEventMessage;
class PriceTickSizeMessage;
class OrderbookDirectoryMessage;
class TradingStateMessage;
class ShortSellingPriceRestrictionStateMessage;
class OrderAddedWithoutAttributesMessage;
class OrderAddedWithAttributesMessage;
class OrderExecutedMessage;
class OrderDeletedMessage;
class OrderReplacedMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const SecondsMessage&) {}
    virtual void visit(const SystemEventMessage&) {}
    virtual void visit(const PriceTickSizeMessage&) {}
    virtual void visit(const OrderbookDirectoryMessage&) {}
    virtual void visit(const TradingStateMessage&) {}
    virtual void visit(const ShortSellingPriceRestrictionStateMessage&) {}
    virtual void visit(const OrderAddedWithoutAttributesMessage&) {}
    virtual void visit(const OrderAddedWithAttributesMessage&) {}
    virtual void visit(const OrderExecutedMessage&) {}
    virtual void visit(const OrderDeletedMessage&) {}
    virtual void visit(const OrderReplacedMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

} // namespace jnx::jnxequities::pts::itch::v1_6
