#include "MessageType.hpp"

namespace cboe::c1options::complex::pitch::v2_1_18 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::TimeMessage: return "Time Message";
        case MessageType::UnitClearMessage: return "Unit Clear Message";
        case MessageType::TransactionBegin: return "Transaction Begin";
        case MessageType::TransactionEndMessage: return "Transaction End Message";
        case MessageType::ComplexInstrumentDefinitionExpandedMessage: return "Complex Instrument Definition Expanded Message";
        case MessageType::SymbolMappingMessage: return "Symbol Mapping Message";
        case MessageType::AddOrderLongMessage: return "Add Order Long Message";
        case MessageType::AddOrderShortMessage: return "Add Order Short Message";
        case MessageType::AddOrderExpandedMessage: return "Add Order Expanded Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::OrderExecutedAtPriceSizeMessage: return "Order Executed At Price Size Message";
        case MessageType::ReduceSizeLongMessage: return "Reduce Size Long Message";
        case MessageType::ReduceSizeShortMessage: return "Reduce Size Short Message";
        case MessageType::ModifyOrderLongMessage: return "Modify Order Long Message";
        case MessageType::ModifyOrderShortMessage: return "Modify Order Short Message";
        case MessageType::DeleteOrderMessage: return "Delete Order Message";
        case MessageType::TradeLongMessage: return "Trade Long Message";
        case MessageType::TradeShortMessage: return "Trade Short Message";
        case MessageType::AuctionNotificationMessage: return "Auction Notification Message";
        case MessageType::AuctionCancelMessage: return "Auction Cancel Message";
        case MessageType::AuctionTradeMessage: return "Auction Trade Message";
        case MessageType::TradingStatusMessage: return "Trading Status Message";
        case MessageType::AuctionUpdateMessage: return "Auction Update Message";
        case MessageType::AuctionSummaryMessage: return "Auction Summary Message";
        case MessageType::EndOfSessionMessage: return "End Of Session Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::c1options::complex::pitch::v2_1_18
