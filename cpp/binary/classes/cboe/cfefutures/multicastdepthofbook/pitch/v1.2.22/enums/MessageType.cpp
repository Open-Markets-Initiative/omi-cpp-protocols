#include "MessageType.hpp"

namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::TimeReferenceMessage: return "Time Reference Message";
        case MessageType::TimeMessage: return "Time Message";
        case MessageType::UnitClearMessage: return "Unit Clear Message";
        case MessageType::FuturesInstrumentDefinitionMessage: return "Futures Instrument Definition Message";
        case MessageType::FuturesVarianceSymbolMappingMessage: return "Futures Variance Symbol Mapping Message";
        case MessageType::PriceLimitsMessage: return "Price Limits Message";
        case MessageType::AddOrderLongMessage: return "Add Order Long Message";
        case MessageType::AddOrderShortMessage: return "Add Order Short Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::ReduceSizeLongMessage: return "Reduce Size Long Message";
        case MessageType::ReduceSizeShortMessage: return "Reduce Size Short Message";
        case MessageType::ModifyOrderLongMessage: return "Modify Order Long Message";
        case MessageType::ModifyOrderShortMessage: return "Modify Order Short Message";
        case MessageType::DeleteOrderMessage: return "Delete Order Message";
        case MessageType::TradeLongMessage: return "Trade Long Message";
        case MessageType::TradeShortMessage: return "Trade Short Message";
        case MessageType::TransactionBeginMessage: return "Transaction Begin Message";
        case MessageType::TransactionEndMessage: return "Transaction End Message";
        case MessageType::TradeBreakMessage: return "Trade Break Message";
        case MessageType::SettlementMessage: return "Settlement Message";
        case MessageType::OpenInterestMessage: return "Open Interest Message";
        case MessageType::EndOfDaySummaryMessage: return "End Of Day Summary Message";
        case MessageType::TradingStatusMessage: return "Trading Status Message";
        case MessageType::EndOfSessionMessage: return "End Of Session Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::cfefutures::multicastdepthofbook::pitch::v1_2_22
