#include "MessageType.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

std::string_view to_string(MessageType value) {
    switch (value) {
        case MessageType::TimestampMessage: return "Timestamp Message";
        case MessageType::SystemEventMessage: return "System Event Message";
        case MessageType::OptionsDirectoryMessage: return "Options Directory Message";
        case MessageType::TradingActionMessage: return "Trading Action Message";
        case MessageType::SecurityOpenClosedMessage: return "Security Open Closed Message";
        case MessageType::ShortBestBidAndAskUpdateMessage: return "Short Best Bid And Ask Update Message";
        case MessageType::LongBestBidAndAskUpdateMessage: return "Long Best Bid And Ask Update Message";
        case MessageType::ShortBestAskUpdateMessage: return "Short Best Ask Update Message";
        case MessageType::ShortBestBidUpdateMessage: return "Short Best Bid Update Message";
        case MessageType::LongBestAskUpdateMessage: return "Long Best Ask Update Message";
        case MessageType::LongBestBidUpdateMessage: return "Long Best Bid Update Message";
        case MessageType::TradeReportMessage: return "Trade Report Message";
        case MessageType::BrokenTradeReportMessage: return "Broken Trade Report Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, MessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
