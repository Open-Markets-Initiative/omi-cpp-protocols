#include "Factory.hpp"

#include "definitions.hpp"

namespace miax::miaxoptions::complextopofmarket::mach::v1_1 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case ApplicationMessage::message_type: return std::make_unique<ApplicationMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<Data> DataFactory::create(DataCode code) {
    switch (code) {
        case SystemTimeMessage::message_type: return std::make_unique<SystemTimeMessage>();
        case SeriesUpdate::message_type: return std::make_unique<SeriesUpdate>();
        case ComplexStrategyDefinitionMessage::message_type: return std::make_unique<ComplexStrategyDefinitionMessage>();
        case SystemStateMessage::message_type: return std::make_unique<SystemStateMessage>();
        case CompactComplexTopOfMarketBidMessage::message_type: return std::make_unique<CompactComplexTopOfMarketBidMessage>();
        case CompactComplexTopOfMarketOfferMessage::message_type: return std::make_unique<CompactComplexTopOfMarketOfferMessage>();
        case WideComplexTopOfMarketBidMessage::message_type: return std::make_unique<WideComplexTopOfMarketBidMessage>();
        case WideComplexTopOfMarketOfferMessage::message_type: return std::make_unique<WideComplexTopOfMarketOfferMessage>();
        case CompactComplexDoubleSidedTopOfMarketMessage::message_type: return std::make_unique<CompactComplexDoubleSidedTopOfMarketMessage>();
        case WideComplexDoubleSidedTopOfMarketMessage::message_type: return std::make_unique<WideComplexDoubleSidedTopOfMarketMessage>();
        case StrategyTradeMessage::message_type: return std::make_unique<StrategyTradeMessage>();
        case UnderlyingTradingStatusMessage::message_type: return std::make_unique<UnderlyingTradingStatusMessage>();
        default: return std::make_unique<UnknownData>(code);
    }
}

} // namespace miax::miaxoptions::complextopofmarket::mach::v1_1
