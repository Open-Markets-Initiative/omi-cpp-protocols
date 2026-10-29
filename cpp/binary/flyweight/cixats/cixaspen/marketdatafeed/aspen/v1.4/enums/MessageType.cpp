#include "MessageType.hpp"

namespace cixats::cixaspen::marketdatafeed::aspen::v1_4 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::MarketEventMessage: return "Market Event Message";
        case MessageType::SymbolInformationMessage: return "Symbol Information Message";
        case MessageType::SymbolStateMessage: return "Symbol State Message";
        case MessageType::NewOrderAddMessage: return "New Order Add Message";
        case MessageType::OrderPartialCancelMessage: return "Order Partial Cancel Message";
        case MessageType::OrderCancelAllMessage: return "Order Cancel All Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::TradeMessage: return "Trade Message";
        case MessageType::TradeCancelMessage: return "Trade Cancel Message";
        case MessageType::TradeCorrectMessage: return "Trade Correct Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace cixats::cixaspen::marketdatafeed::aspen::v1_4
