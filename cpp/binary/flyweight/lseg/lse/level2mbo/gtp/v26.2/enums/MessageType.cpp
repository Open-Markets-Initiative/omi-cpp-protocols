#include "MessageType.hpp"

namespace lseg::lse::level2mbo::gtp::v26_2 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::InstrumentDirectoryMessage: return "Instrument Directory Message";
        case MessageType::InstrumentStatusMessage: return "Instrument Status Message";
        case MessageType::AddOrderMboMessage: return "Add Order Mbo Message";
        case MessageType::AddOrderShortMboMessage: return "Add Order Short Mbo Message";
        case MessageType::OrderBookClearMessage: return "Order Book Clear Message";
        case MessageType::TradeMessage: return "Trade Message";
        case MessageType::StatisticsMessage: return "Statistics Message";
        case MessageType::StatisticsUpdateMessage: return "Statistics Update Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << static_cast<long long>(value);
}

} // namespace lseg::lse::level2mbo::gtp::v26_2
