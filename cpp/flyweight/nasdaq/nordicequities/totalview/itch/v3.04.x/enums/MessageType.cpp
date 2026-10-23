#include "MessageType.hpp"

namespace nasdaq::nordicequities::totalview::itch::v3_04_x {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::OrderBookTradingActionMessage: return "Order Book Trading Action Message";
        case MessageType::OrderBookDirectoryMessage: return "Order Book Directory Message";
        case MessageType::AddOrderMessage: return "Add Order Message";
        case MessageType::AddOrderMpidAttributionMessage: return "Add Order Mpid Attribution Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::OrderExecutedWithPriceMessage: return "Order Executed With Price Message";
        case MessageType::OrderCancelMessage: return "Order Cancel Message";
        case MessageType::OrderDeleteMessage: return "Order Delete Message";
        case MessageType::OrderBookFlushMessage: return "Order Book Flush Message";
        case MessageType::OrderReplaceMessage: return "Order Replace Message";
        case MessageType::TradeMessage: return "Trade Message";
        case MessageType::CrossTradeMessage: return "Cross Trade Message";
        case MessageType::BrokenTradeMessage: return "Broken Trade Message";
        case MessageType::NoiiMessage: return "Noii Message";
        case MessageType::MoiiMessage: return "Moii Message";
        case MessageType::ExecutionSummaryMessage: return "Execution Summary Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nordicequities::totalview::itch::v3_04_x
