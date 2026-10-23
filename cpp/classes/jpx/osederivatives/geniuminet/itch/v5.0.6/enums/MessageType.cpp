#include "MessageType.hpp"

namespace jpx::osederivatives::geniuminet::itch::v5_0_6 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SecondsMessage: return "Seconds Message";
        case MessageType::OrderBookDirectory: return "Order Book Directory";
        case MessageType::CombinationOrderbookLeg: return "Combination Orderbook Leg";
        case MessageType::TickSizeTableEntry: return "Tick Size Table Entry";
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::OrderBookStateMessage: return "Order Book State Message";
        case MessageType::AddOrderNoMpid: return "Add Order No Mpid";
        case MessageType::AddOrderWithMpid: return "Add Order With Mpid";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::OrderExecutedWithPriceMessage: return "Order Executed With Price Message";
        case MessageType::OrderReplaceMessage: return "Order Replace Message";
        case MessageType::OrderDeleteMessage: return "Order Delete Message";
        case MessageType::TradeMessage: return "Trade Message";
        case MessageType::EquilibriumPriceUpdate: return "Equilibrium Price Update";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jpx::osederivatives::geniuminet::itch::v5_0_6
