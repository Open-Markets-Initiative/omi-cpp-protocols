#include "MessageType.hpp"

namespace jnx::jnxequities::pts::itch::v1_6 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SecondsMessage: return "Seconds Message";
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::PriceTickSizeMessage: return "Price Tick Size Message";
        case MessageType::OrderbookDirectoryMessage: return "Orderbook Directory Message";
        case MessageType::TradingStateMessage: return "Trading State Message";
        case MessageType::ShortSellingPriceRestrictionStateMessage: return "Short Selling Price Restriction State Message";
        case MessageType::OrderAddedWithoutAttributesMessage: return "Order Added Without Attributes Message";
        case MessageType::OrderAddedWithAttributesMessage: return "Order Added With Attributes Message";
        case MessageType::OrderExecutedMessage: return "Order Executed Message";
        case MessageType::OrderDeletedMessage: return "Order Deleted Message";
        case MessageType::OrderReplacedMessage: return "Order Replaced Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::itch::v1_6
