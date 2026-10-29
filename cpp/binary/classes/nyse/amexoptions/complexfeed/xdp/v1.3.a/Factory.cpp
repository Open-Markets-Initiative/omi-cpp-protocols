#include "Factory.hpp"

#include "definitions.hpp"

namespace nyse::amexoptions::complexfeed::xdp::v1_3_a {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case ComplexQuoteMessage::message_type: return std::make_unique<ComplexQuoteMessage>();
        case ComplexTradeMessage::message_type: return std::make_unique<ComplexTradeMessage>();
        case ComplexCrossingRfqMessage::message_type: return std::make_unique<ComplexCrossingRfqMessage>();
        case ComplexCubeRfqMessage::message_type: return std::make_unique<ComplexCubeRfqMessage>();
        case ComplexStatusMessage::message_type: return std::make_unique<ComplexStatusMessage>();
        case RefreshComplexQuoteMessage::message_type: return std::make_unique<RefreshComplexQuoteMessage>();
        case RefreshComplexTradeMessage::message_type: return std::make_unique<RefreshComplexTradeMessage>();
        case ComplexSymbolDefinitionMessage::message_type: return std::make_unique<ComplexSymbolDefinitionMessage>();
        case StreamIdMessage::message_type: return std::make_unique<StreamIdMessage>();
        case SequenceNumberResetMessage::message_type: return std::make_unique<SequenceNumberResetMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace nyse::amexoptions::complexfeed::xdp::v1_3_a
