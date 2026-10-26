#include "MessageType.hpp"

namespace miax::pearlequities::depthofmarket::mach::v1_3_d {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemTimeMessage: return "System Time Message";
        case MessageType::SymbolUpdateMessage: return "Symbol Update Message";
        case MessageType::SystemStateMessage: return "System State Message";
        case MessageType::SecurityTradingStatusNotificationMessage: return "Security Trading Status Notification Message";
        case MessageType::SymbolClearMessage: return "Symbol Clear Message";
        case MessageType::AddOrderMessage: return "Add Order Message";
        case MessageType::ModifyOrderMessage: return "Modify Order Message";
        case MessageType::DeleteOrderMessage: return "Delete Order Message";
        case MessageType::OrderExecutionMessage: return "Order Execution Message";
        case MessageType::TradeMessage: return "Trade Message";
        case MessageType::TradeCancelMessage: return "Trade Cancel Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace miax::pearlequities::depthofmarket::mach::v1_3_d
