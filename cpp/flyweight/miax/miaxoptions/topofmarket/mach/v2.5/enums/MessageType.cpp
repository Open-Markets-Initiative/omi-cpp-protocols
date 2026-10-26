#include "MessageType.hpp"

namespace miax::miaxoptions::topofmarket::mach::v2_5 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemTimeMessage: return "System Time Message";
        case MessageType::SimpleSeriesUpdateMessage: return "Simple Series Update Message";
        case MessageType::SystemStateMessage: return "System State Message";
        case MessageType::SimpleTopOfMarketBestBidOrOfferCompactBidMessage: return "Simple Top Of Market Best Bid Or Offer Compact Bid Message";
        case MessageType::SimpleTopOfMarketBestBidOrOfferCompactOfferMessage: return "Simple Top Of Market Best Bid Or Offer Compact Offer Message";
        case MessageType::SimpleTopOfMarketBestBidOrOfferWideBidMessage: return "Simple Top Of Market Best Bid Or Offer Wide Bid Message";
        case MessageType::SimpleTopOfMarketBestBidOrOfferWideOfferMessage: return "Simple Top Of Market Best Bid Or Offer Wide Offer Message";
        case MessageType::SimpleDoubleSidedTopOfMarketBestBidOrOfferCompactMessage: return "Simple Double Sided Top Of Market Best Bid Or Offer Compact Message";
        case MessageType::SimpleDoubleSidedTopOfMarketBestBidOrOfferWideMessage: return "Simple Double Sided Top Of Market Best Bid Or Offer Wide Message";
        case MessageType::LastSaleMessage: return "Last Sale Message";
        case MessageType::TradeCancelMessage: return "Trade Cancel Message";
        case MessageType::UnderlyingTradingStatusNotificationMessage: return "Underlying Trading Status Notification Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace miax::miaxoptions::topofmarket::mach::v2_5
