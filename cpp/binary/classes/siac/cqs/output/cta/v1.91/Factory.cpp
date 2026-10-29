#include "Factory.hpp"

#include "definitions.hpp"

namespace siac::cqs::output::cta::v1_91 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case AdministrativeMessage::message_type: return std::make_unique<AdministrativeMessage>();
        case ControlMessage::message_type: return std::make_unique<ControlMessage>();
        case MarketStatusMessage::message_type: return std::make_unique<MarketStatusMessage>();
        case QuoteMessage::message_type: return std::make_unique<QuoteMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<AdministrativeMessagePayload> AdministrativeMessagePayloadFactory::create(AdministrativeMessagePayloadCode code) {
    switch (code) {
        case AdministrativeUnformattedMessage::message_type: return std::make_unique<AdministrativeUnformattedMessage>();
        default: return std::make_unique<UnknownAdministrativeMessagePayload>(code);
    }
}

std::unique_ptr<ControlMessagePayload> ControlMessagePayloadFactory::create(ControlMessagePayloadCode code) {
    switch (code) {
        case StartOfDayMessage::message_type: return std::make_unique<StartOfDayMessage>();
        case FinraCloseMessage::message_type: return std::make_unique<FinraCloseMessage>();
        case ResetBlockSequenceNumberMessage::message_type: return std::make_unique<ResetBlockSequenceNumberMessage>();
        case StartOfTestCycleMessage::message_type: return std::make_unique<StartOfTestCycleMessage>();
        case EndOfTestCycleMessage::message_type: return std::make_unique<EndOfTestCycleMessage>();
        case FinraOpenMessage::message_type: return std::make_unique<FinraOpenMessage>();
        case DisasterRecoveryDataCenterActivationMessage::message_type: return std::make_unique<DisasterRecoveryDataCenterActivationMessage>();
        case LineIntegrityMessage::message_type: return std::make_unique<LineIntegrityMessage>();
        case EndOfDayMessage::message_type: return std::make_unique<EndOfDayMessage>();
        default: return std::make_unique<UnknownControlMessagePayload>(code);
    }
}

std::unique_ptr<MarketStatusMessagePayload> MarketStatusMessagePayloadFactory::create(MarketStatusMessagePayloadCode code) {
    switch (code) {
        case MarketWideCircuitBreakerDeclineLevelStatusMessage::message_type: return std::make_unique<MarketWideCircuitBreakerDeclineLevelStatusMessage>();
        case MarketWideCircuitBreakerStatusMessage::message_type: return std::make_unique<MarketWideCircuitBreakerStatusMessage>();
        default: return std::make_unique<UnknownMarketStatusMessagePayload>(code);
    }
}

std::unique_ptr<QuoteMessagePayload> QuoteMessagePayloadFactory::create(QuoteMessagePayloadCode code) {
    switch (code) {
        case AuctionStatusMessage::message_type: return std::make_unique<AuctionStatusMessage>();
        case LongQuoteMessage::message_type: return std::make_unique<LongQuoteMessage>();
        case ShortQuoteMessage::message_type: return std::make_unique<ShortQuoteMessage>();
        case SpecialLongQuoteMessage::message_type: return std::make_unique<SpecialLongQuoteMessage>();
        default: return std::make_unique<UnknownQuoteMessagePayload>(code);
    }
}

} // namespace siac::cqs::output::cta::v1_91
