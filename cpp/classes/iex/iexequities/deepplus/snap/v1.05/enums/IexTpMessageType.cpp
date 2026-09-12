#include "IexTpMessageType.hpp"

namespace iex::iexequities::deepplus::snap::v1_05 {

std::string_view to_string(IexTpMessageType value) {
    switch (value) {
        case IexTpMessageType::SystemEventMessage: return "System Event Message";
        case IexTpMessageType::SecurityDirectoryMessage: return "Security Directory Message";
        case IexTpMessageType::TradingStatusMessage: return "Trading Status Message";
        case IexTpMessageType::RetailLiquidityIndicatorMessage: return "Retail Liquidity Indicator Message";
        case IexTpMessageType::OperationalHaltStatusMessage: return "Operational Halt Status Message";
        case IexTpMessageType::ShortSalePriceTestStatusMessage: return "Short Sale Price Test Status Message";
        case IexTpMessageType::SecurityEventMessage: return "Security Event Message";
        case IexTpMessageType::AddOrderMessage: return "Add Order Message";
        case IexTpMessageType::OrderModifyMessage: return "Order Modify Message";
        case IexTpMessageType::OrderDeleteMessage: return "Order Delete Message";
        case IexTpMessageType::OrderExecutedMessage: return "Order Executed Message";
        case IexTpMessageType::TradeMessage: return "Trade Message";
        case IexTpMessageType::TradeBreakMessage: return "Trade Break Message";
        case IexTpMessageType::ClearBookMessage: return "Clear Book Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, IexTpMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace iex::iexequities::deepplus::snap::v1_05
