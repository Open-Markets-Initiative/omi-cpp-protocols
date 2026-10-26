#include "SequencedMessageType.hpp"

namespace nasdaq::nomoptions::itto::itch::v4_0_2025 {

std::string_view to_string(SequencedMessageType value) {
    switch (value) {
        case SequencedMessageType::SystemEventMessage: return "System Event Message";
        case SequencedMessageType::OptionsDirectoryMessage: return "Options Directory Message";
        case SequencedMessageType::TradingActionMessage: return "Trading Action Message";
        case SequencedMessageType::SecurityOpenMessage: return "Security Open Message";
        case SequencedMessageType::AddOrderMessageShortMessageForm: return "Add Order Message Short Message Form";
        case SequencedMessageType::AddOrderMessageLongFormMessage: return "Add Order Message Long Form Message";
        case SequencedMessageType::AddQuoteMessageShortFormMessage: return "Add Quote Message Short Form Message";
        case SequencedMessageType::AddQuoteMessageLongFormMessage: return "Add Quote Message Long Form Message";
        case SequencedMessageType::SingleSideExecutedMessage: return "Single Side Executed Message";
        case SequencedMessageType::SingleSideExecutedWithPriceMessage: return "Single Side Executed With Price Message";
        case SequencedMessageType::OrderCancelMessage: return "Order Cancel Message";
        case SequencedMessageType::SingleSideReplaceMessageShortForm: return "Single Side Replace Message Short Form";
        case SequencedMessageType::SingleSideReplaceMessageLongForm: return "Single Side Replace Message Long Form";
        case SequencedMessageType::SingleSideDeleteMessage: return "Single Side Delete Message";
        case SequencedMessageType::SingleSideChangeMessage: return "Single Side Change Message";
        case SequencedMessageType::QuoteReplaceMessageShortForm: return "Quote Replace Message Short Form";
        case SequencedMessageType::QuoteReplaceMessageLongForm: return "Quote Replace Message Long Form";
        case SequencedMessageType::QuoteDeleteMessage: return "Quote Delete Message";
        case SequencedMessageType::OptionsTradeMessagesNonAuction: return "Options Trade Messages Non Auction";
        case SequencedMessageType::OptionsCrossTradeMessage: return "Options Cross Trade Message";
        case SequencedMessageType::BrokenTradeOrderExecutedMessage: return "Broken Trade Order Executed Message";
        case SequencedMessageType::NoiiMessage: return "Noii Message";
        case SequencedMessageType::EndOfReplaySequenceMessage: return "End Of Replay Sequence Message";
        default: return {};
    }
}

std::ostream& operator<<(std::ostream& out, SequencedMessageType value) {
    const auto name = to_string(value);
    if (!name.empty()) { return out << name; }
    return out << '\'' << static_cast<char>(value) << '\'';
}

} // namespace nasdaq::nomoptions::itto::itch::v4_0_2025
