#include "MessageType.hpp"

namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::ComplexStrategyDirectoryMessage: return "Complex Strategy Directory Message";
        case MessageType::StrategyOpenClosedMessage: return "Strategy Open Closed Message";
        case MessageType::StrategyTradingActionMessage: return "Strategy Trading Action Message";
        case MessageType::StrategyBestBidAndAskUpdate: return "Strategy Best Bid And Ask Update";
        case MessageType::StrategyBestBidUpdate: return "Strategy Best Bid Update";
        case MessageType::StrategyBestAskUpdate: return "Strategy Best Ask Update";
        case MessageType::ComplexStrategyTickerMessage: return "Complex Strategy Ticker Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::iseoptions::topcomboquotefeed::itch::v1_0
