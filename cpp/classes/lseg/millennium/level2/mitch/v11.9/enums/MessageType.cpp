#include "MessageType.hpp"

namespace lseg::millennium::level2::mitch::v11_9 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::TimeMessage: return "Time Message";
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::SymbolDirectoryMessage: return "Symbol Directory Message";
        case MessageType::SymbolStatusMessage: return "Symbol Status Message";
        case MessageType::AddOrderMessage: return "Add Order Message";
        case MessageType::AddAttributedOrderMessage: return "Add Attributed Order Message";
        case MessageType::OrderDeletedMessage: return "Order Deleted Message";
        case MessageType::OrderModifiedMessage: return "Order Modified Message";
        case MessageType::OrderBookClearMessage: return "Order Book Clear Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::OrderExecutedWithPriceSizeMessage: return "Order Executed With Price Size Message";
        case MessageType::TradeMessage: return "Trade Message";
        case MessageType::AuctionTradeMessage: return "Auction Trade Message";
        case MessageType::AuctionInfoMessage: return "Auction Info Message";
        case MessageType::StatisticsMessage: return "Statistics Message";
        case MessageType::TopOfBookMessage: return "Top Of Book Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::millennium::level2::mitch::v11_9
