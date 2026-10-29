#include "MessageType.hpp"

namespace otcmarkets::linkats::multicast::link::v4_3 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::StartOfSpinMessage: return "Start Of Spin Message";
        case MessageType::EndOfSpinMessage: return "End Of Spin Message";
        case MessageType::MarketOpenMessage: return "Market Open Message";
        case MessageType::MarketCloseMessage: return "Market Close Message";
        case MessageType::SecurityMessage: return "Security Message";
        case MessageType::QuoteMessage: return "Quote Message";
        case MessageType::QuoteUpdateMessage: return "Quote Update Message";
        case MessageType::InsideMessage: return "Inside Message";
        case MessageType::InsideUpdateMessage: return "Inside Update Message";
        case MessageType::ReferencePriceMessage: return "Reference Price Message";
        case MessageType::ReferencePriceUpdateMessage: return "Reference Price Update Message";
        case MessageType::ExtendedSecurityMessage: return "Extended Security Message";
        case MessageType::ExtendedSecurityNoCusipMessage: return "Extended Security No Cusip Message";
        case MessageType::TradeMessage: return "Trade Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace otcmarkets::linkats::multicast::link::v4_3
