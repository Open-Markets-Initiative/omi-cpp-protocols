#include "Factory.hpp"

#include "definitions.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SystemEventMessage::message_type: return std::make_unique<SystemEventMessage>();
        case ComplexStrategyDirectoryMessage::message_type: return std::make_unique<ComplexStrategyDirectoryMessage>();
        case StrategyTradingActionMessage::message_type: return std::make_unique<StrategyTradingActionMessage>();
        case StrategyOpenClosedMessage::message_type: return std::make_unique<StrategyOpenClosedMessage>();
        case ComplexStrategyOrderOnBookMessage::message_type: return std::make_unique<ComplexStrategyOrderOnBookMessage>();
        case ComplexStrategyAuctionMessage::message_type: return std::make_unique<ComplexStrategyAuctionMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
