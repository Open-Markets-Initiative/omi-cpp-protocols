#pragma once

namespace siac::cqs::output::cta::v1_91 {

class AdministrativeMessage;
class ControlMessage;
class MarketStatusMessage;
class QuoteMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const AdministrativeMessage&) {}
    virtual void visit(const ControlMessage&) {}
    virtual void visit(const MarketStatusMessage&) {}
    virtual void visit(const QuoteMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

class AdministrativeUnformattedMessage;
class UnknownAdministrativeMessagePayload;

// What the messages of the Administrative Message Payload dispatch are handed to,
// reached through the administrative_message_payload a AdministrativeMessage holds.
class AdministrativeMessagePayloadVisitor {
  public:
    virtual ~AdministrativeMessagePayloadVisitor() = default;

    virtual void visit(const AdministrativeUnformattedMessage&) {}
    virtual void visit(const UnknownAdministrativeMessagePayload&) {}
};

class StartOfDayMessage;
class FinraCloseMessage;
class ResetBlockSequenceNumberMessage;
class StartOfTestCycleMessage;
class EndOfTestCycleMessage;
class FinraOpenMessage;
class DisasterRecoveryDataCenterActivationMessage;
class LineIntegrityMessage;
class EndOfDayMessage;
class UnknownControlMessagePayload;

// What the messages of the Control Message Payload dispatch are handed to,
// reached through the control_message_payload a ControlMessage holds.
class ControlMessagePayloadVisitor {
  public:
    virtual ~ControlMessagePayloadVisitor() = default;

    virtual void visit(const StartOfDayMessage&) {}
    virtual void visit(const FinraCloseMessage&) {}
    virtual void visit(const ResetBlockSequenceNumberMessage&) {}
    virtual void visit(const StartOfTestCycleMessage&) {}
    virtual void visit(const EndOfTestCycleMessage&) {}
    virtual void visit(const FinraOpenMessage&) {}
    virtual void visit(const DisasterRecoveryDataCenterActivationMessage&) {}
    virtual void visit(const LineIntegrityMessage&) {}
    virtual void visit(const EndOfDayMessage&) {}
    virtual void visit(const UnknownControlMessagePayload&) {}
};

class MarketWideCircuitBreakerDeclineLevelStatusMessage;
class MarketWideCircuitBreakerStatusMessage;
class UnknownMarketStatusMessagePayload;

// What the messages of the Market Status Message Payload dispatch are handed to,
// reached through the market_status_message_payload a MarketStatusMessage holds.
class MarketStatusMessagePayloadVisitor {
  public:
    virtual ~MarketStatusMessagePayloadVisitor() = default;

    virtual void visit(const MarketWideCircuitBreakerDeclineLevelStatusMessage&) {}
    virtual void visit(const MarketWideCircuitBreakerStatusMessage&) {}
    virtual void visit(const UnknownMarketStatusMessagePayload&) {}
};

class AuctionStatusMessage;
class LongQuoteMessage;
class ShortQuoteMessage;
class SpecialLongQuoteMessage;
class UnknownQuoteMessagePayload;

// What the messages of the Quote Message Payload dispatch are handed to,
// reached through the quote_message_payload a QuoteMessage holds.
class QuoteMessagePayloadVisitor {
  public:
    virtual ~QuoteMessagePayloadVisitor() = default;

    virtual void visit(const AuctionStatusMessage&) {}
    virtual void visit(const LongQuoteMessage&) {}
    virtual void visit(const ShortQuoteMessage&) {}
    virtual void visit(const SpecialLongQuoteMessage&) {}
    virtual void visit(const UnknownQuoteMessagePayload&) {}
};

} // namespace siac::cqs::output::cta::v1_91
