#include "MessageType.hpp"

namespace asx::asxderivatives::ntp::itch::v1_05 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SecondsMessage: return "Seconds Message";
        case MessageType::EndOfBusinessTradeDateMessage: return "End Of Business Trade Date Message";
        case MessageType::FutureSymbolDirectoryMessage: return "Future Symbol Directory Message";
        case MessageType::OptionsSymbolDirectoryMessage: return "Options Symbol Directory Message";
        case MessageType::CombinationSymbolDirectoryMessage: return "Combination Symbol Directory Message";
        case MessageType::BundlesSymbolDirectory: return "Bundles Symbol Directory";
        case MessageType::OrderBookStateMessage: return "Order Book State Message";
        case MessageType::AddOrderMessage: return "Add Order Message";
        case MessageType::OrderVolumeCancelledMessage: return "Order Volume Cancelled Message";
        case MessageType::OrderDeletedMessage: return "Order Deleted Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::AuctionOrderExecutedMessage: return "Auction Order Executed Message";
        case MessageType::CombinationOrderExecutedMessage: return "Combination Order Executed Message";
        case MessageType::ImpliedOrderAddedMessage: return "Implied Order Added Message";
        case MessageType::ImpliedOrderReplacedMessage: return "Implied Order Replaced Message";
        case MessageType::ImpliedOrderDeletedMessage: return "Implied Order Deleted Message";
        case MessageType::TradeExecutedMessage: return "Trade Executed Message";
        case MessageType::CombinationTradeExecutedMessage: return "Combination Trade Executed Message";
        case MessageType::TradeCancellationMessage: return "Trade Cancellation Message";
        case MessageType::EquilibriumPriceMessage: return "Equilibrium Price Message";
        case MessageType::OpenHighLowLastTradeAdjustmentMessage: return "Open High Low Last Trade Adjustment Message";
        case MessageType::MarketSettlementMessage: return "Market Settlement Message";
        case MessageType::TextMessage: return "Text Message";
        case MessageType::RequestForQuoteMessage: return "Request For Quote Message";
        case MessageType::AnomalousOrderThresholdPublishMessage: return "Anomalous Order Threshold Publish Message";
        case MessageType::VolumeAndOpenInterestMessage: return "Volume And Open Interest Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace asx::asxderivatives::ntp::itch::v1_05
