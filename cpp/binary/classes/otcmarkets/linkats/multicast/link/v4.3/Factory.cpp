#include "Factory.hpp"

#include "definitions.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::unique_ptr<Message> Factory::create(MessageCode code) {
    switch (code) {
        case StartOfSpinMessage::message_type: return std::make_unique<StartOfSpinMessage>();
        case EndOfSpinMessage::message_type: return std::make_unique<EndOfSpinMessage>();
        case MarketOpenMessage::message_type: return std::make_unique<MarketOpenMessage>();
        case MarketCloseMessage::message_type: return std::make_unique<MarketCloseMessage>();
        case SecurityMessage::message_type: return std::make_unique<SecurityMessage>();
        case QuoteMessage::message_type: return std::make_unique<QuoteMessage>();
        case QuoteUpdateMessage::message_type: return std::make_unique<QuoteUpdateMessage>();
        case InsideMessage::message_type: return std::make_unique<InsideMessage>();
        case InsideUpdateMessage::message_type: return std::make_unique<InsideUpdateMessage>();
        case ReferencePriceMessage::message_type: return std::make_unique<ReferencePriceMessage>();
        case ReferencePriceUpdateMessage::message_type: return std::make_unique<ReferencePriceUpdateMessage>();
        case ExtendedSecurityMessage::message_type: return std::make_unique<ExtendedSecurityMessage>();
        case ExtendedSecurityNoCusipMessage::message_type: return std::make_unique<ExtendedSecurityNoCusipMessage>();
        case TradeMessage::message_type: return std::make_unique<TradeMessage>();
        default: return std::make_unique<UnknownMessage>(code);
    }
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
