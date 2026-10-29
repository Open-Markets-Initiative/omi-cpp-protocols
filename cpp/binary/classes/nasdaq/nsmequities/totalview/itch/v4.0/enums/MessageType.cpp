#include "MessageType.hpp"

namespace nasdaq::nsmequities::totalview::itch::v4_0 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::TimestampMessage: return "Timestamp Message";
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::StockDirectoryMessage: return "Stock Directory Message";
        case MessageType::StockTradingActionMessage: return "Stock Trading Action Message";
        case MessageType::MarketParticipantPositionMessage: return "Market Participant Position Message";
        case MessageType::AddOrderMessage: return "Add Order Message";
        case MessageType::AddOrderWithMpidMessage: return "Add Order With Mpid Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::OrderExecutedWithPriceMessage: return "Order Executed With Price Message";
        case MessageType::OrderCancelMessage: return "Order Cancel Message";
        case MessageType::OrderDeleteMessage: return "Order Delete Message";
        case MessageType::OrderReplaceMessage: return "Order Replace Message";
        case MessageType::TradeMessage: return "Trade Message";
        case MessageType::CrossTradeMessage: return "Cross Trade Message";
        case MessageType::BrokenTradeMessage: return "Broken Trade Message";
        case MessageType::NetOrderImbalanceIndicatorMessage: return "Net Order Imbalance Indicator Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nsmequities::totalview::itch::v4_0
