#include "Factory.hpp"

#include "definitions.hpp"

namespace bse::bseindia::eobi::fbe::v1_4 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case HeartbeatMessage::message_type: return std::make_unique<HeartbeatMessage>();
        case ProductSummaryMessage::message_type: return std::make_unique<ProductSummaryMessage>();
        case SnapshotOrderMessage::message_type: return std::make_unique<SnapshotOrderMessage>();
        case InstrumentSummaryMessage::message_type: return std::make_unique<InstrumentSummaryMessage>();
        case AuctionBestBidOfferMessage::message_type: return std::make_unique<AuctionBestBidOfferMessage>();
        case AuctionClearingPriceMessage::message_type: return std::make_unique<AuctionClearingPriceMessage>();
        case TopOfBookMessage::message_type: return std::make_unique<TopOfBookMessage>();
        case OrderAddMessage::message_type: return std::make_unique<OrderAddMessage>();
        case OrderModifyMessage::message_type: return std::make_unique<OrderModifyMessage>();
        case OrderModifySamePriorityMessage::message_type: return std::make_unique<OrderModifySamePriorityMessage>();
        case OrderDeleteMessage::message_type: return std::make_unique<OrderDeleteMessage>();
        case OrderMassDeleteMessage::message_type: return std::make_unique<OrderMassDeleteMessage>();
        case PartialOrderExecutionMessage::message_type: return std::make_unique<PartialOrderExecutionMessage>();
        case FullOrderExecutionMessage::message_type: return std::make_unique<FullOrderExecutionMessage>();
        case TradeReversalMessage::message_type: return std::make_unique<TradeReversalMessage>();
        case ExecutionSummaryMessage::message_type: return std::make_unique<ExecutionSummaryMessage>();
        case InstrumentInfoMessage::message_type: return std::make_unique<InstrumentInfoMessage>();
        case LppRangeMessage::message_type: return std::make_unique<LppRangeMessage>();
        case ProductStateChangeMessage::message_type: return std::make_unique<ProductStateChangeMessage>();
        case InstrumentStateChangeMessage::message_type: return std::make_unique<InstrumentStateChangeMessage>();
        case AddComplexInstrumentMessage::message_type: return std::make_unique<AddComplexInstrumentMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace bse::bseindia::eobi::fbe::v1_4
