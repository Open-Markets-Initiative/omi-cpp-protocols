#include "Factory.hpp"

#include "definitions.hpp"

namespace siac::opra::output::obi::v6_2 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case AdministrativeCategory::message_type: return std::make_unique<AdministrativeCategory>();
        case ControlCategory::message_type: return std::make_unique<ControlCategory>();
        case EquityAndIndexLastSaleCategory::message_type: return std::make_unique<EquityAndIndexLastSaleCategory>();
        case OpenInterestCategory::message_type: return std::make_unique<OpenInterestCategory>();
        case EquityAndIndexEndOfDaySummaryCategory::message_type: return std::make_unique<EquityAndIndexEndOfDaySummaryCategory>();
        case LongEquityAndIndexQuoteCategory::message_type: return std::make_unique<LongEquityAndIndexQuoteCategory>();
        case ShortEquityAndIndexQuoteCategory::message_type: return std::make_unique<ShortEquityAndIndexQuoteCategory>();
        case UnderlyingValueCategory::message_type: return std::make_unique<UnderlyingValueCategory>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<AdministrativeMessagePayload> AdministrativeMessagePayloadFactory::create(AdministrativeMessagePayloadCode code) {
    switch (code) {
        case AdministrativeMessage::message_type: return std::make_unique<AdministrativeMessage>();
        default: return std::make_unique<UnknownAdministrativeMessagePayload>(code);
    }
}

std::unique_ptr<ControlMessagePayload> ControlMessagePayloadFactory::create(ControlMessagePayloadCode code) {
    switch (code) {
        case ControlMessage::message_type: case ControlMessageType::StartOfSummary: case ControlMessageType::EndOfSummary: case ControlMessageType::EndOfDay: case ControlMessageType::ResetBlockSequenceNumber: case ControlMessageType::StartOfOpenInterest: case ControlMessageType::EndOfOpenInterest: case ControlMessageType::LineIntegrity: case ControlMessageType::DisasterRecoveryDataCenterActivation: { auto message = std::make_unique<ControlMessage>(); message->set_type(code); return message; }
        default: return std::make_unique<UnknownControlMessagePayload>(code);
    }
}

std::unique_ptr<EquityAndIndexLastSaleMessagePayload> EquityAndIndexLastSaleMessagePayloadFactory::create(EquityAndIndexLastSaleMessagePayloadCode code) {
    switch (code) {
        case EquityAndIndexLastSaleMessage::message_type: case EquityAndIndexLastSaleMessageType::Oseq: case EquityAndIndexLastSaleMessageType::Cncl: case EquityAndIndexLastSaleMessageType::Late: case EquityAndIndexLastSaleMessageType::Cnco: case EquityAndIndexLastSaleMessageType::Open: case EquityAndIndexLastSaleMessageType::Cnol: case EquityAndIndexLastSaleMessageType::Opnl: case EquityAndIndexLastSaleMessageType::Auto: case EquityAndIndexLastSaleMessageType::Reop: case EquityAndIndexLastSaleMessageType::Ajst: case EquityAndIndexLastSaleMessageType::Sprd: case EquityAndIndexLastSaleMessageType::Stdl: case EquityAndIndexLastSaleMessageType::Stpd: case EquityAndIndexLastSaleMessageType::Cstp: case EquityAndIndexLastSaleMessageType::Bwrt: case EquityAndIndexLastSaleMessageType::Cmbo: case EquityAndIndexLastSaleMessageType::Spim: case EquityAndIndexLastSaleMessageType::Isoi: case EquityAndIndexLastSaleMessageType::Bnmt: case EquityAndIndexLastSaleMessageType::Xmpt: { auto message = std::make_unique<EquityAndIndexLastSaleMessage>(); message->set_type(code); return message; }
        default: return std::make_unique<UnknownEquityAndIndexLastSaleMessagePayload>(code);
    }
}

std::unique_ptr<OpenInterestMessagePayload> OpenInterestMessagePayloadFactory::create(OpenInterestMessagePayloadCode code) {
    switch (code) {
        case OpenInterestMessage::message_type: return std::make_unique<OpenInterestMessage>();
        default: return std::make_unique<UnknownOpenInterestMessagePayload>(code);
    }
}

std::unique_ptr<EquityAndIndexEndOfDaySummaryMessagePayload> EquityAndIndexEndOfDaySummaryMessagePayloadFactory::create(EquityAndIndexEndOfDaySummaryMessagePayloadCode code) {
    switch (code) {
        case EquityAndIndexEndOfDaySummaryMessage::message_type: return std::make_unique<EquityAndIndexEndOfDaySummaryMessage>();
        default: return std::make_unique<UnknownEquityAndIndexEndOfDaySummaryMessagePayload>(code);
    }
}

std::unique_ptr<LongEquityAndIndexQuoteMessagePayload> LongEquityAndIndexQuoteMessagePayloadFactory::create(LongEquityAndIndexQuoteMessagePayloadCode code) {
    switch (code) {
        case LongEquityAndIndexQuoteMessage::message_type: case LongEquityAndIndexQuoteMessageType::NonFirmQuote: case LongEquityAndIndexQuoteMessageType::IndicativeValue: case LongEquityAndIndexQuoteMessageType::Rotation: case LongEquityAndIndexQuoteMessageType::TradingHalted: case LongEquityAndIndexQuoteMessageType::EligibleForAutomaticExecution: case LongEquityAndIndexQuoteMessageType::BidContainsCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::OfferContainsCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::BothBidAndOfferContainCustomerTradingInterest: case LongEquityAndIndexQuoteMessageType::OfferSideOfQuoteNotFirmBidSideFirm: case LongEquityAndIndexQuoteMessageType::BidSideOfQuoteNotFirmOfferSideFirm: { auto message = std::make_unique<LongEquityAndIndexQuoteMessage>(); message->set_type(code); return message; }
        default: return std::make_unique<UnknownLongEquityAndIndexQuoteMessagePayload>(code);
    }
}

std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> ShortEquityAndIndexQuoteMessagePayloadFactory::create(ShortEquityAndIndexQuoteMessagePayloadCode code) {
    switch (code) {
        case ShortEquityAndIndexQuoteMessage::message_type: case ShortEquityAndIndexQuoteMessageType::NonFirmQuote: case ShortEquityAndIndexQuoteMessageType::IndicativeValue: case ShortEquityAndIndexQuoteMessageType::Rotation: case ShortEquityAndIndexQuoteMessageType::TradingHalted: case ShortEquityAndIndexQuoteMessageType::EligibleForAutomaticExecution: case ShortEquityAndIndexQuoteMessageType::BidContainsCustomerTradingInterest: case ShortEquityAndIndexQuoteMessageType::OfferContainsCustomerTradingInterest: case ShortEquityAndIndexQuoteMessageType::BothBidAndOfferContainCustomerTradingInterest: case ShortEquityAndIndexQuoteMessageType::OfferSideOfQuoteNotFirmBidSideFirm: case ShortEquityAndIndexQuoteMessageType::BidSideOfQuoteNotFirmOfferSideFirm: { auto message = std::make_unique<ShortEquityAndIndexQuoteMessage>(); message->set_type(code); return message; }
        default: return std::make_unique<UnknownShortEquityAndIndexQuoteMessagePayload>(code);
    }
}

std::unique_ptr<UnderlyingValueMessagePayload> UnderlyingValueMessagePayloadFactory::create(UnderlyingValueMessagePayloadCode code) {
    switch (code) {
        case UnderlyingValueLastSaleMessage::message_type: return std::make_unique<UnderlyingValueLastSaleMessage>();
        case UnderlyingValueBidAndOfferMessage::message_type: return std::make_unique<UnderlyingValueBidAndOfferMessage>();
        default: return std::make_unique<UnknownUnderlyingValueMessagePayload>(code);
    }
}

} // namespace siac::opra::output::obi::v6_2
