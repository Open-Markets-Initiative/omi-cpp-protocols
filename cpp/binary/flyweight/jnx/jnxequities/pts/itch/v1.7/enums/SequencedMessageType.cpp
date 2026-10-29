#include "SequencedMessageType.hpp"

namespace jnx::jnxequities::pts::itch::v1_7 {

std::string_view to_string(SequencedMessageType value) {
    switch (value) {
        case SequencedMessageType::TimestampSecondsMessage: return "Timestamp Seconds Message";
        case SequencedMessageType::SystemEventMessage: return "System Event Message";
        case SequencedMessageType::PriceTickSizeMessage: return "Price Tick Size Message";
        case SequencedMessageType::OrderbookDirectoryMessage: return "Orderbook Directory Message";
        case SequencedMessageType::TradingStateMessage: return "Trading State Message";
        case SequencedMessageType::ShortSellingPriceRestrictionStateMessage: return "Short Selling Price Restriction State Message";
        case SequencedMessageType::OrderAddedWithoutAttributesMessage: return "Order Added Without Attributes Message";
        case SequencedMessageType::OrderAddedWithAttributesMessage: return "Order Added With Attributes Message";
        case SequencedMessageType::OrderExecutedMessage: return "Order Executed Message";
        case SequencedMessageType::OrderDeletedMessage: return "Order Deleted Message";
        case SequencedMessageType::OrderReplacedMessage: return "Order Replaced Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SequencedMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace jnx::jnxequities::pts::itch::v1_7
