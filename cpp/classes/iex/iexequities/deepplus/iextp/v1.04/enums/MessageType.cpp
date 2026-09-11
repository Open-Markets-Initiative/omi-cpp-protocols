#include "MessageType.hpp"

namespace iex::iexequities::deepplus::iextp::v1_04 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::SecurityDirectoryMessage: return "Security Directory Message";
        case MessageType::TradingStatusMessage: return "Trading Status Message";
        case MessageType::RetailLiquidityIndicatorMessage: return "Retail Liquidity Indicator Message";
        case MessageType::OperationalHaltStatusMessage: return "Operational Halt Status Message";
        case MessageType::ShortSalePriceTestStatusMessage: return "Short Sale Price Test Status Message";
        case MessageType::SecurityEventMessage: return "Security Event Message";
        case MessageType::AddOrderMessage: return "Add Order Message";
        case MessageType::OrderModifyMessage: return "Order Modify Message";
        case MessageType::OrderDeleteMessage: return "Order Delete Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::TradeMessage: return "Trade Message";
        case MessageType::TradeBreakMessage: return "Trade Break Message";
        case MessageType::ClearBookMessage: return "Clear Book Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deepplus::iextp::v1_04
