#pragma once

namespace siac::cts::output::cta::v2_10 {

class AdministrativeMessage;
class ControlMessage;
class IndicesMessage;
class MarketStatusMessage;
class PriorDayMessage;
class SummaryMessage;
class TradeMessage;
class UnknownMessage;

// What a packet's messages are dispatched to. Derive from it, override the visits you
// care about, and hand it to the packet's accept or a message's; the others do nothing.
class Visitor {
  public:
    virtual ~Visitor() = default;

    virtual void visit(const AdministrativeMessage&) {}
    virtual void visit(const ControlMessage&) {}
    virtual void visit(const IndicesMessage&) {}
    virtual void visit(const MarketStatusMessage&) {}
    virtual void visit(const PriorDayMessage&) {}
    virtual void visit(const SummaryMessage&) {}
    virtual void visit(const TradeMessage&) {}
    virtual void visit(const UnknownMessage&) {}
};

class StartOfEndOfDayMessage;
class EndOfEndOfDayMessage;
class StartOfStartOfDayMessage;
class EndOfStartOfDayMessage;
class UnknownAdministrativeMessagePayload;

// What the messages of the Administrative Message Payload dispatch are handed to,
// reached through the administrative_message_payload a AdministrativeMessage holds.
class AdministrativeMessagePayloadVisitor {
  public:
    virtual ~AdministrativeMessagePayloadVisitor() = default;

    virtual void visit(const StartOfEndOfDayMessage&) {}
    virtual void visit(const EndOfEndOfDayMessage&) {}
    virtual void visit(const StartOfStartOfDayMessage&) {}
    virtual void visit(const EndOfStartOfDayMessage&) {}
    virtual void visit(const UnknownAdministrativeMessagePayload&) {}
};

class StartOfDayMessage;
class ResetBlockSequenceNumberMessage;
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
    virtual void visit(const ResetBlockSequenceNumberMessage&) {}
    virtual void visit(const DisasterRecoveryDataCenterActivationMessage&) {}
    virtual void visit(const LineIntegrityMessage&) {}
    virtual void visit(const EndOfDayMessage&) {}
    virtual void visit(const UnknownControlMessagePayload&) {}
};

class IndexMessage;
class BidAndOfferIndexMessage;
class UnknownIndicesMessagePayload;

// What the messages of the Indices Message Payload dispatch are handed to,
// reached through the indices_message_payload a IndicesMessage holds.
class IndicesMessagePayloadVisitor {
  public:
    virtual ~IndicesMessagePayloadVisitor() = default;

    virtual void visit(const IndexMessage&) {}
    virtual void visit(const BidAndOfferIndexMessage&) {}
    virtual void visit(const UnknownIndicesMessagePayload&) {}
};

class MarketWideCircuitBreakerDeclineLevelStatusMessage;
class MarketWideCircuitBreakerStatusMessage;
class ApproximateAdjustedVolumeMarketCenterMessage;
class FractionalApproximateAdjustedVolumeMarketCenterMessage;
class ApproximateTradesAndTotalDollarValueMessage;
class CrossingSessionSummaryMessage;
class UnknownMarketStatusMessagePayload;

// What the messages of the Market Status Message Payload dispatch are handed to,
// reached through the market_status_message_payload a MarketStatusMessage holds.
class MarketStatusMessagePayloadVisitor {
  public:
    virtual ~MarketStatusMessagePayloadVisitor() = default;

    virtual void visit(const MarketWideCircuitBreakerDeclineLevelStatusMessage&) {}
    virtual void visit(const MarketWideCircuitBreakerStatusMessage&) {}
    virtual void visit(const ApproximateAdjustedVolumeMarketCenterMessage&) {}
    virtual void visit(const FractionalApproximateAdjustedVolumeMarketCenterMessage&) {}
    virtual void visit(const ApproximateTradesAndTotalDollarValueMessage&) {}
    virtual void visit(const CrossingSessionSummaryMessage&) {}
    virtual void visit(const UnknownMarketStatusMessagePayload&) {}
};

class PriorDayTradeCorrectionMessage;
class FractionalPriorDayTradeCorrectionMessage;
class PriorDayTradeMessage;
class FractionalPriorDayTradeMessage;
class PriorDayTradeCancelErrorMessage;
class FractionalPriorDayTradeCancelErrorMessage;
class UnknownPriorDayMessagePayload;

// What the messages of the Prior Day Message Payload dispatch are handed to,
// reached through the prior_day_message_payload a PriorDayMessage holds.
class PriorDayMessagePayloadVisitor {
  public:
    virtual ~PriorDayMessagePayloadVisitor() = default;

    virtual void visit(const PriorDayTradeCorrectionMessage&) {}
    virtual void visit(const FractionalPriorDayTradeCorrectionMessage&) {}
    virtual void visit(const PriorDayTradeMessage&) {}
    virtual void visit(const FractionalPriorDayTradeMessage&) {}
    virtual void visit(const PriorDayTradeCancelErrorMessage&) {}
    virtual void visit(const FractionalPriorDayTradeCancelErrorMessage&) {}
    virtual void visit(const UnknownPriorDayMessagePayload&) {}
};

class ConsolidatedStartOfDaySummaryMessage;
class ParticipantStartOfDaySummaryMessage;
class ConsolidatedEndOfDaySummaryMessage;
class FractionalConsolidatedEndOfDaySummaryMessage;
class ParticipantEndOfDaySummaryMessage;
class FractionalParticipantEndOfDaySummaryMessage;
class UnknownSummaryMessagePayload;

// What the messages of the Summary Message Payload dispatch are handed to,
// reached through the summary_message_payload a SummaryMessage holds.
class SummaryMessagePayloadVisitor {
  public:
    virtual ~SummaryMessagePayloadVisitor() = default;

    virtual void visit(const ConsolidatedStartOfDaySummaryMessage&) {}
    virtual void visit(const ParticipantStartOfDaySummaryMessage&) {}
    virtual void visit(const ConsolidatedEndOfDaySummaryMessage&) {}
    virtual void visit(const FractionalConsolidatedEndOfDaySummaryMessage&) {}
    virtual void visit(const ParticipantEndOfDaySummaryMessage&) {}
    virtual void visit(const FractionalParticipantEndOfDaySummaryMessage&) {}
    virtual void visit(const UnknownSummaryMessagePayload&) {}
};

class AuctionStatusMessage;
class TradeCorrectionMessage;
class FractionalTradeCorrectionMessage;
class LongTradeMessage;
class FractionalLongTradeMessage;
class TradingStatusMessage;
class ShortTradeMessage;
class FractionalShortTradeMessage;
class TradeCancelErrorMessage;
class FractionalTradeCancelErrorMessage;
class UnknownTradeMessagePayload;

// What the messages of the Trade Message Payload dispatch are handed to,
// reached through the trade_message_payload a TradeMessage holds.
class TradeMessagePayloadVisitor {
  public:
    virtual ~TradeMessagePayloadVisitor() = default;

    virtual void visit(const AuctionStatusMessage&) {}
    virtual void visit(const TradeCorrectionMessage&) {}
    virtual void visit(const FractionalTradeCorrectionMessage&) {}
    virtual void visit(const LongTradeMessage&) {}
    virtual void visit(const FractionalLongTradeMessage&) {}
    virtual void visit(const TradingStatusMessage&) {}
    virtual void visit(const ShortTradeMessage&) {}
    virtual void visit(const FractionalShortTradeMessage&) {}
    virtual void visit(const TradeCancelErrorMessage&) {}
    virtual void visit(const FractionalTradeCancelErrorMessage&) {}
    virtual void visit(const UnknownTradeMessagePayload&) {}
};

} // namespace siac::cts::output::cta::v2_10
