#include "Factory.hpp"

#include "definitions.hpp"

namespace eurex::t7::eobi::fbe::v6_0 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case AddComplexInstrument::message_type: return std::make_unique<AddComplexInstrument>();
        case AuctionBbo::message_type: return std::make_unique<AuctionBbo>();
        case AuctionClearingPrice::message_type: return std::make_unique<AuctionClearingPrice>();
        case CrossRequest::message_type: return std::make_unique<CrossRequest>();
        case ExecutionSummary::message_type: return std::make_unique<ExecutionSummary>();
        case FullOrderExecution::message_type: return std::make_unique<FullOrderExecution>();
        case Heartbeat::message_type: return std::make_unique<Heartbeat>();
        case InstrumentStateChange::message_type: return std::make_unique<InstrumentStateChange>();
        case InstrumentSummary::message_type: return std::make_unique<InstrumentSummary>();
        case OrderAdd::message_type: return std::make_unique<OrderAdd>();
        case OrderDelete::message_type: return std::make_unique<OrderDelete>();
        case OrderMassDelete::message_type: return std::make_unique<OrderMassDelete>();
        case OrderModify::message_type: return std::make_unique<OrderModify>();
        case OrderModifySamePrio::message_type: return std::make_unique<OrderModifySamePrio>();
        case PartialOrderExecution::message_type: return std::make_unique<PartialOrderExecution>();
        case ProductStateChange::message_type: return std::make_unique<ProductStateChange>();
        case ProductSummary::message_type: return std::make_unique<ProductSummary>();
        case QuoteRequest::message_type: return std::make_unique<QuoteRequest>();
        case SnapshotOrder::message_type: return std::make_unique<SnapshotOrder>();
        case TopOfBook::message_type: return std::make_unique<TopOfBook>();
        case TradeReport::message_type: return std::make_unique<TradeReport>();
        case TradeReversal::message_type: return std::make_unique<TradeReversal>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace eurex::t7::eobi::fbe::v6_0
