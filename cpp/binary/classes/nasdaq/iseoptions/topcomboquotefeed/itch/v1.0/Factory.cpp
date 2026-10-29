#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case ComplexStrategyDirectoryMessage::message_type: return std::make_unique<ComplexStrategyDirectoryMessage>();
        case StrategyOpenClosedMessage::message_type: return std::make_unique<StrategyOpenClosedMessage>();
        case StrategyTradingActionMessage::message_type: return std::make_unique<StrategyTradingActionMessage>();
        case StrategyBestBidAndAskUpdate::message_type: return std::make_unique<StrategyBestBidAndAskUpdate>();
        case StrategyBestBidUpdate::message_type: return std::make_unique<StrategyBestBidUpdate>();
        case StrategyBestAskUpdate::message_type: return std::make_unique<StrategyBestAskUpdate>();
        case ComplexStrategyTickerMessage::message_type: return std::make_unique<ComplexStrategyTickerMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
