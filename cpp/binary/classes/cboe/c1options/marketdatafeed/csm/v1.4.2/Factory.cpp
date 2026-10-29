#include "Factory.hpp"

#include "definitions.hpp"

namespace cboe::c1options::marketdatafeed::csm::v1_4_2 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SecurityDefinitionMessage::message_type: return std::make_unique<SecurityDefinitionMessage>();
        case CurrentMarketRefreshMessage::message_type: return std::make_unique<CurrentMarketRefreshMessage>();
        case MarketDataRefreshMessage::message_type: return std::make_unique<MarketDataRefreshMessage>();
        case CurrentMarketUpdateMessage::message_type: return std::make_unique<CurrentMarketUpdateMessage>();
        case RecapUpdateMessage::message_type: return std::make_unique<RecapUpdateMessage>();
        case TickerMessage::message_type: return std::make_unique<TickerMessage>();
        case ExpectedOpeningPriceAndSizeMessage::message_type: return std::make_unique<ExpectedOpeningPriceAndSizeMessage>();
        case IndexValueMessage::message_type: return std::make_unique<IndexValueMessage>();
        case SettlementValueMessage::message_type: return std::make_unique<SettlementValueMessage>();
        case SummaryMessage::message_type: return std::make_unique<SummaryMessage>();
        case MarketDataControlMessage::message_type: return std::make_unique<MarketDataControlMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace cboe::c1options::marketdatafeed::csm::v1_4_2
