#include "MessageType.hpp"

namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::ComplexStrategyDirectoryMessage: return "Complex Strategy Directory Message";
        case MessageType::StrategyTradingActionMessage: return "Strategy Trading Action Message";
        case MessageType::StrategyOpenClosedMessage: return "Strategy Open Closed Message";
        case MessageType::ComplexStrategyOrderOnBookMessage: return "Complex Strategy Order On Book Message";
        case MessageType::ComplexStrategyAuctionMessage: return "Complex Strategy Auction Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::ordercombofeed::itch::v1_1
