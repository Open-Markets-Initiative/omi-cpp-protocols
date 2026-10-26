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
        case ControlMessage::message_type: return std::make_unique<ControlMessage>();
        default: return std::make_unique<UnknownControlMessagePayload>(code);
    }
}

std::unique_ptr<EquityAndIndexLastSaleMessagePayload> EquityAndIndexLastSaleMessagePayloadFactory::create(EquityAndIndexLastSaleMessagePayloadCode code) {
    switch (code) {
        case EquityAndIndexLastSaleMessage::message_type: return std::make_unique<EquityAndIndexLastSaleMessage>();
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
        case LongEquityAndIndexQuoteMessage::message_type: return std::make_unique<LongEquityAndIndexQuoteMessage>();
        default: return std::make_unique<UnknownLongEquityAndIndexQuoteMessagePayload>(code);
    }
}

std::unique_ptr<ShortEquityAndIndexQuoteMessagePayload> ShortEquityAndIndexQuoteMessagePayloadFactory::create(ShortEquityAndIndexQuoteMessagePayloadCode code) {
    switch (code) {
        case ShortEquityAndIndexQuoteMessage::message_type: return std::make_unique<ShortEquityAndIndexQuoteMessage>();
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
