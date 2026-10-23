#include "Factory.hpp"

#include "definitions.hpp"

namespace memx::memxequities::memoirdepthfeed::sbe::v1_3 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case SequencedMessage::message_type: return std::make_unique<SequencedMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<Payload> PayloadFactory::create(PayloadCode code) {
    switch (code) {
        case InstrumentDirectoryMessage::message_type: return std::make_unique<InstrumentDirectoryMessage>();
        case RegShoRestrictionMessage::message_type: return std::make_unique<RegShoRestrictionMessage>();
        case SecurityTradingStatusMessage::message_type: return std::make_unique<SecurityTradingStatusMessage>();
        case TradingSessionStatusMessage::message_type: return std::make_unique<TradingSessionStatusMessage>();
        case OrderAddedMessage::message_type: return std::make_unique<OrderAddedMessage>();
        case OrderDeletedMessage::message_type: return std::make_unique<OrderDeletedMessage>();
        case OrderReducedMessage::message_type: return std::make_unique<OrderReducedMessage>();
        case OrderExecutedMessage::message_type: return std::make_unique<OrderExecutedMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        case BrokenTradeMessage::message_type: return std::make_unique<BrokenTradeMessage>();
        case CorrectedTradeMessage::message_type: return std::make_unique<CorrectedTradeMessage>();
        case ClearBookMessage::message_type: return std::make_unique<ClearBookMessage>();
        case SnapshotCompleteMessage::message_type: return std::make_unique<SnapshotCompleteMessage>();
        default: return std::make_unique<UnknownPayload>(code);
    }
}

} // namespace memx::memxequities::memoirdepthfeed::sbe::v1_3
