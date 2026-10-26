#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::nsmequities::qbbo::itch::v2_1 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case StockDirectoryMessage::message_type: return std::make_unique<StockDirectoryMessage>();
        case StockTradingActionMessage::message_type: return std::make_unique<StockTradingActionMessage>();
        case RegShoRestrictionMessage::message_type: return std::make_unique<RegShoRestrictionMessage>();
        case MwcbDeclineLevelMessage::message_type: return std::make_unique<MwcbDeclineLevelMessage>();
        case MwcbBreachMessage::message_type: return std::make_unique<MwcbBreachMessage>();
        case OperationalHaltMessage::message_type: return std::make_unique<OperationalHaltMessage>();
        case BboQuotationMessage::message_type: return std::make_unique<BboQuotationMessage>();
        case PriceImprovementMessage::message_type: return std::make_unique<PriceImprovementMessage>();
        case IpoQuotingPeriodUpdateMessage::message_type: return std::make_unique<IpoQuotingPeriodUpdateMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nasdaq::nsmequities::qbbo::itch::v2_1
