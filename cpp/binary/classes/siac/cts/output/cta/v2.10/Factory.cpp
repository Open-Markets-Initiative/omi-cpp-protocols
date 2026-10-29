#include "Factory.hpp"

#include "definitions.hpp"

namespace siac::cts::output::cta::v2_10 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case AdministrativeMessage::message_type: return std::make_unique<AdministrativeMessage>();
        case ControlMessage::message_type: return std::make_unique<ControlMessage>();
        case IndicesMessage::message_type: return std::make_unique<IndicesMessage>();
        case MarketStatusMessage::message_type: return std::make_unique<MarketStatusMessage>();
        case PriorDayMessage::message_type: return std::make_unique<PriorDayMessage>();
        case SummaryMessage::message_type: return std::make_unique<SummaryMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<AdministrativeMessagePayload> AdministrativeMessagePayloadFactory::create(AdministrativeMessagePayloadCode code) {
    switch (code) {
        case StartOfEndOfDayMessage::message_type: return std::make_unique<StartOfEndOfDayMessage>();
        case EndOfEndOfDayMessage::message_type: return std::make_unique<EndOfEndOfDayMessage>();
        case StartOfStartOfDayMessage::message_type: return std::make_unique<StartOfStartOfDayMessage>();
        case EndOfStartOfDayMessage::message_type: return std::make_unique<EndOfStartOfDayMessage>();
        default: return std::make_unique<UnknownAdministrativeMessagePayload>(code);
    }
}

std::unique_ptr<ControlMessagePayload> ControlMessagePayloadFactory::create(ControlMessagePayloadCode code) {
    switch (code) {
        case StartOfDayMessage::message_type: return std::make_unique<StartOfDayMessage>();
        case ResetBlockSequenceNumberMessage::message_type: return std::make_unique<ResetBlockSequenceNumberMessage>();
        case DisasterRecoveryDataCenterActivationMessage::message_type: return std::make_unique<DisasterRecoveryDataCenterActivationMessage>();
        case LineIntegrityMessage::message_type: return std::make_unique<LineIntegrityMessage>();
        case EndOfDayMessage::message_type: return std::make_unique<EndOfDayMessage>();
        default: return std::make_unique<UnknownControlMessagePayload>(code);
    }
}

std::unique_ptr<IndicesMessagePayload> IndicesMessagePayloadFactory::create(IndicesMessagePayloadCode code) {
    switch (code) {
        case IndexMessage::message_type: return std::make_unique<IndexMessage>();
        case BidAndOfferIndexMessage::message_type: return std::make_unique<BidAndOfferIndexMessage>();
        default: return std::make_unique<UnknownIndicesMessagePayload>(code);
    }
}

std::unique_ptr<MarketStatusMessagePayload> MarketStatusMessagePayloadFactory::create(MarketStatusMessagePayloadCode code) {
    switch (code) {
        case MarketWideCircuitBreakerDeclineLevelStatusMessage::message_type: return std::make_unique<MarketWideCircuitBreakerDeclineLevelStatusMessage>();
        case MarketWideCircuitBreakerStatusMessage::message_type: return std::make_unique<MarketWideCircuitBreakerStatusMessage>();
        case ApproximateAdjustedVolumeMarketCenterMessage::message_type: return std::make_unique<ApproximateAdjustedVolumeMarketCenterMessage>();
        case FractionalApproximateAdjustedVolumeMarketCenterMessage::message_type: return std::make_unique<FractionalApproximateAdjustedVolumeMarketCenterMessage>();
        case ApproximateTradesAndTotalDollarValueMessage::message_type: return std::make_unique<ApproximateTradesAndTotalDollarValueMessage>();
        case CrossingSessionSummaryMessage::message_type: return std::make_unique<CrossingSessionSummaryMessage>();
        default: return std::make_unique<UnknownMarketStatusMessagePayload>(code);
    }
}

std::unique_ptr<PriorDayMessagePayload> PriorDayMessagePayloadFactory::create(PriorDayMessagePayloadCode code) {
    switch (code) {
        case PriorDayTradeCorrectionMessage::message_type: return std::make_unique<PriorDayTradeCorrectionMessage>();
        case FractionalPriorDayTradeCorrectionMessage::message_type: return std::make_unique<FractionalPriorDayTradeCorrectionMessage>();
        case PriorDayTradeMessage::message_type: return std::make_unique<PriorDayTradeMessage>();
        case FractionalPriorDayTradeMessage::message_type: return std::make_unique<FractionalPriorDayTradeMessage>();
        case PriorDayTradeCancelErrorMessage::message_type: return std::make_unique<PriorDayTradeCancelErrorMessage>();
        case FractionalPriorDayTradeCancelErrorMessage::message_type: return std::make_unique<FractionalPriorDayTradeCancelErrorMessage>();
        default: return std::make_unique<UnknownPriorDayMessagePayload>(code);
    }
}

std::unique_ptr<SummaryMessagePayload> SummaryMessagePayloadFactory::create(SummaryMessagePayloadCode code) {
    switch (code) {
        case ConsolidatedStartOfDaySummaryMessage::message_type: return std::make_unique<ConsolidatedStartOfDaySummaryMessage>();
        case ParticipantStartOfDaySummaryMessage::message_type: return std::make_unique<ParticipantStartOfDaySummaryMessage>();
        case ConsolidatedEndOfDaySummaryMessage::message_type: return std::make_unique<ConsolidatedEndOfDaySummaryMessage>();
        case FractionalConsolidatedEndOfDaySummaryMessage::message_type: return std::make_unique<FractionalConsolidatedEndOfDaySummaryMessage>();
        case ParticipantEndOfDaySummaryMessage::message_type: return std::make_unique<ParticipantEndOfDaySummaryMessage>();
        case FractionalParticipantEndOfDaySummaryMessage::message_type: return std::make_unique<FractionalParticipantEndOfDaySummaryMessage>();
        default: return std::make_unique<UnknownSummaryMessagePayload>(code);
    }
}

std::unique_ptr<TradeMessagePayload> TradeMessagePayloadFactory::create(TradeMessagePayloadCode code) {
    switch (code) {
        case AuctionStatusMessage::message_type: return std::make_unique<AuctionStatusMessage>();
        case TradeCorrectionMessage::message_type: return std::make_unique<TradeCorrectionMessage>();
        case FractionalTradeCorrectionMessage::message_type: return std::make_unique<FractionalTradeCorrectionMessage>();
        case LongTradeMessage::message_type: return std::make_unique<LongTradeMessage>();
        case FractionalLongTradeMessage::message_type: return std::make_unique<FractionalLongTradeMessage>();
        case TradingStatusMessage::message_type: return std::make_unique<TradingStatusMessage>();
        case ShortTradeMessage::message_type: return std::make_unique<ShortTradeMessage>();
        case FractionalShortTradeMessage::message_type: return std::make_unique<FractionalShortTradeMessage>();
        case TradeCancelErrorMessage::message_type: return std::make_unique<TradeCancelErrorMessage>();
        case FractionalTradeCancelErrorMessage::message_type: return std::make_unique<FractionalTradeCancelErrorMessage>();
        default: return std::make_unique<UnknownTradeMessagePayload>(code);
    }
}

} // namespace siac::cts::output::cta::v2_10
