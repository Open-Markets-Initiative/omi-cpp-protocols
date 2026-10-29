#include "Factory.hpp"

#include "definitions.hpp"

namespace miax::onyxfutures::topofmarket::mach::v1_0_b {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case ApplicationMessage::message_type: return std::make_unique<ApplicationMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

std::unique_ptr<Data> DataFactory::create(DataCode code) {
    switch (code) {
        case SimpleInstrumentDefinitionMessage::message_type: return std::make_unique<SimpleInstrumentDefinitionMessage>();
        case ComplexInstrumentDefinitionMessage::message_type: return std::make_unique<ComplexInstrumentDefinitionMessage>();
        case SystemStateMessage::message_type: return std::make_unique<SystemStateMessage>();
        case InstrumentTradingStatusNotificationMessage::message_type: return std::make_unique<InstrumentTradingStatusNotificationMessage>();
        case BestBidAndOfferMessage::message_type: return std::make_unique<BestBidAndOfferMessage>();
        case LastSaleMessage::message_type: return std::make_unique<LastSaleMessage>();
        case TradeCancelMessage::message_type: return std::make_unique<TradeCancelMessage>();
        default: return std::make_unique<UnknownData>(code);
    }
}

} // namespace miax::onyxfutures::topofmarket::mach::v1_0_b
