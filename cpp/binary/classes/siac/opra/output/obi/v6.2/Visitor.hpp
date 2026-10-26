#pragma once

namespace siac::opra::output::obi::v6_2 {

class AdministrativeCategory;
class ControlCategory;
class EquityAndIndexLastSaleCategory;
class OpenInterestCategory;
class EquityAndIndexEndOfDaySummaryCategory;
class LongEquityAndIndexQuoteCategory;
class ShortEquityAndIndexQuoteCategory;
class UnderlyingValueCategory;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const AdministrativeCategory&) {}
    virtual void visit(const ControlCategory&) {}
    virtual void visit(const EquityAndIndexLastSaleCategory&) {}
    virtual void visit(const OpenInterestCategory&) {}
    virtual void visit(const EquityAndIndexEndOfDaySummaryCategory&) {}
    virtual void visit(const LongEquityAndIndexQuoteCategory&) {}
    virtual void visit(const ShortEquityAndIndexQuoteCategory&) {}
    virtual void visit(const UnderlyingValueCategory&) {}
    virtual void visit(const UnknownMessage&) {}
};

class AdministrativeMessage;
class UnknownAdministrativeMessagePayload;

// What the messages of the Administrative Message Payload dispatch are handed to,
// reached through the administrative_message_payload a AdministrativeCategory holds.
class AdministrativeMessagePayloadVisitor {
  public:
    virtual ~AdministrativeMessagePayloadVisitor() = default;

    virtual void visit(const AdministrativeMessage&) {}
    virtual void visit(const UnknownAdministrativeMessagePayload&) {}
};

class ControlMessage;
class UnknownControlMessagePayload;

// What the messages of the Control Message Payload dispatch are handed to,
// reached through the control_message_payload a ControlCategory holds.
class ControlMessagePayloadVisitor {
  public:
    virtual ~ControlMessagePayloadVisitor() = default;

    virtual void visit(const ControlMessage&) {}
    virtual void visit(const UnknownControlMessagePayload&) {}
};

class EquityAndIndexLastSaleMessage;
class UnknownEquityAndIndexLastSaleMessagePayload;

// What the messages of the Equity And Index Last Sale Message Payload dispatch are handed to,
// reached through the equity_and_index_last_sale_message_payload a EquityAndIndexLastSaleCategory holds.
class EquityAndIndexLastSaleMessagePayloadVisitor {
  public:
    virtual ~EquityAndIndexLastSaleMessagePayloadVisitor() = default;

    virtual void visit(const EquityAndIndexLastSaleMessage&) {}
    virtual void visit(const UnknownEquityAndIndexLastSaleMessagePayload&) {}
};

class OpenInterestMessage;
class UnknownOpenInterestMessagePayload;

// What the messages of the Open Interest Message Payload dispatch are handed to,
// reached through the open_interest_message_payload a OpenInterestCategory holds.
class OpenInterestMessagePayloadVisitor {
  public:
    virtual ~OpenInterestMessagePayloadVisitor() = default;

    virtual void visit(const OpenInterestMessage&) {}
    virtual void visit(const UnknownOpenInterestMessagePayload&) {}
};

class EquityAndIndexEndOfDaySummaryMessage;
class UnknownEquityAndIndexEndOfDaySummaryMessagePayload;

// What the messages of the Equity And Index End Of Day Summary Message Payload dispatch are handed to,
// reached through the equity_and_index_end_of_day_summary_message_payload a EquityAndIndexEndOfDaySummaryCategory holds.
class EquityAndIndexEndOfDaySummaryMessagePayloadVisitor {
  public:
    virtual ~EquityAndIndexEndOfDaySummaryMessagePayloadVisitor() = default;

    virtual void visit(const EquityAndIndexEndOfDaySummaryMessage&) {}
    virtual void visit(const UnknownEquityAndIndexEndOfDaySummaryMessagePayload&) {}
};

class LongEquityAndIndexQuoteMessage;
class UnknownLongEquityAndIndexQuoteMessagePayload;

// What the messages of the Long Equity And Index Quote Message Payload dispatch are handed to,
// reached through the long_equity_and_index_quote_message_payload a LongEquityAndIndexQuoteCategory holds.
class LongEquityAndIndexQuoteMessagePayloadVisitor {
  public:
    virtual ~LongEquityAndIndexQuoteMessagePayloadVisitor() = default;

    virtual void visit(const LongEquityAndIndexQuoteMessage&) {}
    virtual void visit(const UnknownLongEquityAndIndexQuoteMessagePayload&) {}
};

class ShortEquityAndIndexQuoteMessage;
class UnknownShortEquityAndIndexQuoteMessagePayload;

// What the messages of the Short Equity And Index Quote Message Payload dispatch are handed to,
// reached through the short_equity_and_index_quote_message_payload a ShortEquityAndIndexQuoteCategory holds.
class ShortEquityAndIndexQuoteMessagePayloadVisitor {
  public:
    virtual ~ShortEquityAndIndexQuoteMessagePayloadVisitor() = default;

    virtual void visit(const ShortEquityAndIndexQuoteMessage&) {}
    virtual void visit(const UnknownShortEquityAndIndexQuoteMessagePayload&) {}
};

class UnderlyingValueLastSaleMessage;
class UnderlyingValueBidAndOfferMessage;
class UnknownUnderlyingValueMessagePayload;

// What the messages of the Underlying Value Message Payload dispatch are handed to,
// reached through the underlying_value_message_payload a UnderlyingValueCategory holds.
class UnderlyingValueMessagePayloadVisitor {
  public:
    virtual ~UnderlyingValueMessagePayloadVisitor() = default;

    virtual void visit(const UnderlyingValueLastSaleMessage&) {}
    virtual void visit(const UnderlyingValueBidAndOfferMessage&) {}
    virtual void visit(const UnknownUnderlyingValueMessagePayload&) {}
};

} // namespace siac::opra::output::obi::v6_2
