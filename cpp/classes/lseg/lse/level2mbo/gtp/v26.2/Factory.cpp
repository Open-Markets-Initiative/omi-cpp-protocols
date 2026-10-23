#include "Factory.hpp"

#include "definitions.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case InstrumentDirectoryMessage::message_type: return std::make_unique<InstrumentDirectoryMessage>();
        case InstrumentStatusMessage::message_type: return std::make_unique<InstrumentStatusMessage>();
        case AddOrderMboMessage::message_type: return std::make_unique<AddOrderMboMessage>();
        case AddOrderShortMboMessage::message_type: return std::make_unique<AddOrderShortMboMessage>();
        case OrderBookClearMessage::message_type: return std::make_unique<OrderBookClearMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case StatisticsMessage::message_type: return std::make_unique<StatisticsMessage>();
        case StatisticsUpdateMessage::message_type: return std::make_unique<StatisticsUpdateMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
