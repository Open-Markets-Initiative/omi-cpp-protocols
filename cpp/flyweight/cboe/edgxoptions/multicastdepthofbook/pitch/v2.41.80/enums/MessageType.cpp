#include "MessageType.hpp"

namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::TimeMessage: return "Time Message";
        case MessageType::UnitClearMessage: return "Unit Clear Message";
        case MessageType::TransactionBeginMessage: return "Transaction Begin Message";
        case MessageType::TransactionEndMessage: return "Transaction End Message";
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
        case MessageType::TradeExpandedMessage: return "Trade Expanded Message";
        case MessageType::TradeBreakMessage: return "Trade Break Message";
        case MessageType::EndOfSessionMessage: return "End Of Session Message";
        case MessageType::SymbolMappingMessage: return "Symbol Mapping Message";
        case MessageType::TradingStatusMessage: return "Trading Status Message";
        case MessageType::WidthUpdateMessage: return "Width Update Message";
        case MessageType::OptionsAuctionUpdateMessage: return "Options Auction Update Message";
        case MessageType::AuctionSummaryMessage: return "Auction Summary Message";
        case MessageType::AuctionNotificationMessage: return "Auction Notification Message";
        case MessageType::AuctionCancelMessage: return "Auction Cancel Message";
        case MessageType::AuctionTradeMessage: return "Auction Trade Message";
        case MessageType::SoqStrikeRangeUpdateMessage: return "Soq Strike Range Update Message";
        case MessageType::ConstituentSymbolMappingMessage: return "Constituent Symbol Mapping Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace cboe::edgxoptions::multicastdepthofbook::pitch::v2_41_80
