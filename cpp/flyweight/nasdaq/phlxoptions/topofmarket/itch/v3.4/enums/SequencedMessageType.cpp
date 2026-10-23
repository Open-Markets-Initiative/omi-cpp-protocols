#include "SequencedMessageType.hpp"

namespace nasdaq::phlxoptions::topofmarket::itch::v3_4 {

std::string_view to_string(SequencedMessageType value) {
    switch (value) {
        case SequencedMessageType::TimestampMessage: return "Timestamp Message";
        case SequencedMessageType::SystemEventMessage: return "System Event Message";
        case SequencedMessageType::OptionsDirectoryMessage: return "Options Directory Message";
        case SequencedMessageType::TradingActionMessage: return "Trading Action Message";
        case SequencedMessageType::SecurityOpenClosedMessage: return "Security Open Closed Message";
        case SequencedMessageType::ShortBestBidAndAskUpdateMessage: return "Short Best Bid And Ask Update Message";
        case SequencedMessageType::LongBestBidAndAskUpdateMessage: return "Long Best Bid And Ask Update Message";
        case SequencedMessageType::ShortBestAskUpdateMessage: return "Short Best Ask Update Message";
        case SequencedMessageType::ShortBestBidUpdateMessage: return "Short Best Bid Update Message";
        case SequencedMessageType::LongBestAskUpdateMessage: return "Long Best Ask Update Message";
        case SequencedMessageType::LongBestBidUpdateMessage: return "Long Best Bid Update Message";
        case SequencedMessageType::TradeReportMessage: return "Trade Report Message";
        case SequencedMessageType::BrokenTradeReportMessage: return "Broken Trade Report Message";
        case SequencedMessageType::EndOfReplaySequenceMessage: return "End Of Replay Sequence Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SequencedMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::phlxoptions::topofmarket::itch::v3_4
