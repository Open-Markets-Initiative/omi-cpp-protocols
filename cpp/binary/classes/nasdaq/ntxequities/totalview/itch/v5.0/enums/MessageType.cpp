#include "MessageType.hpp"

namespace nasdaq::ntxequities::totalview::itch::v5_0 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::StockDirectoryMessage: return "Stock Directory Message";
        case MessageType::StockTradingActionMessage: return "Stock Trading Action Message";
        case MessageType::RegShoShortSalePriceTestRestrictedIndicatorMessage: return "Reg Sho Short Sale Price Test Restricted Indicator Message";
        case MessageType::MarketParticipantPositionMessage: return "Market Participant Position Message";
        case MessageType::MwcbDeclineLevelMessage: return "Mwcb Decline Level Message";
        case MessageType::MwcbStatusMessage: return "Mwcb Status Message";
        case MessageType::LuldAuctionCollarMessage: return "Luld Auction Collar Message";
        case MessageType::OperationalHaltMessage: return "Operational Halt Message";
        case MessageType::AddOrderNoMpidAttributionMessage: return "Add Order No Mpid Attribution Message";
        case MessageType::AddOrderMpidAttributionMessage: return "Add Order Mpid Attribution Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::OrderExecutedWithPriceMessage: return "Order Executed With Price Message";
        case MessageType::OrderCancelMessage: return "Order Cancel Message";
        case MessageType::OrderDeleteMessage: return "Order Delete Message";
        case MessageType::OrderReplaceMessage: return "Order Replace Message";
        case MessageType::NonCrossTradeMessage: return "Non Cross Trade Message";
        case MessageType::CrossTradeMessage: return "Cross Trade Message";
        case MessageType::BrokenTradeMessage: return "Broken Trade Message";
        case MessageType::NetOrderImbalanceIndicatorMessage: return "Net Order Imbalance Indicator Message";
        case MessageType::RetailInterestMessage: return "Retail Interest Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::ntxequities::totalview::itch::v5_0
