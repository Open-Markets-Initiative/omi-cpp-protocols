#include "Factory.hpp"

#include "definitions.hpp"

namespace iex::iexequities::tops::iextp::v1_56 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case QuoteUpdateMessage::message_type: return std::make_unique<QuoteUpdateMessage>();
        case TradeReportMessage::message_type: return std::make_unique<TradeReportMessage>();
        case TradeBreakMessage::message_type: return std::make_unique<TradeBreakMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace iex::iexequities::tops::iextp::v1_56
